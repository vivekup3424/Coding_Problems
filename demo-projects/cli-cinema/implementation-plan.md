cli-nema (CLI Cinema) — Implementation Plan
Context
The project is a greenfield Rust CLI tool that renders video files as ASCII art in real-time with synchronized audio playback. A detailed PRD exists in Claude.md but no code has been written yet. This plan covers the full implementation from cargo init through a polished MVP.

Key Design Decision: ffmpeg-next over opencv
We will use ffmpeg-next for both video AND audio decoding. OpenCV cannot decode audio at all, which would force a hybrid approach (OpenCV for video + ffmpeg CLI for audio to a temp WAV). With ffmpeg-next, one library opens the file, finds both streams, and decodes them with consistent timestamps — making synchronization simpler and more reliable.

Audio will be decoded in-process (not extracted to a temp file via ffmpeg CLI), giving instant playback start and zero disk overhead.

File Structure

cli-cinema/
├── Cargo.toml
├── src/
│   ├── main.rs        — Entry point: CLI parsing, orchestration, error display
│   ├── cli.rs         — clap derive structs for CLI arguments
│   ├── decoder.rs     — Video + audio demuxing/decoding (ffmpeg-next)
│   ├── ascii.rs       — Pixel-to-ASCII conversion, brightness mapping
│   ├── renderer.rs    — crossterm terminal rendering (alternate screen, cursor)
│   ├── audio.rs       — AudioBridge (rodio::Source impl), AudioClock
│   ├── sync.rs        — Master clock logic, frame drop decisions
│   ├── player.rs      — Top-level orchestrator: spawns threads, manages channels
│   ├── error.rs       — Custom error types (thiserror) + Result alias
│   └── types.rs       — Shared data types: AsciiFrame, VideoInfo, PlaybackConfig
Dependencies (Cargo.toml)
Crate	Version	Purpose
clap	4.5 (derive)	Argument parsing
ffmpeg-next	7.0	Video + audio decoding
image	0.25	Fallback image processing
rodio	0.19	Audio playback
crossterm	0.28	Terminal I/O (raw mode, colors, cursor)
crossbeam-channel	0.5	Bounded channels between threads
anyhow	1.0	Application-level error handling
thiserror	2.0	Structured error types
log + env_logger	0.4 / 0.11	Development logging
System prerequisite: FFmpeg dev libraries (apt install libavcodec-dev libavformat-dev libavutil-dev libswscale-dev libswresample-dev).

Architecture
Two-thread Producer/Consumer model:


  Thread A (Decoder)              Thread B (Main/Renderer)
  ┌──────────────────┐            ┌──────────────────────┐
  │ ffmpeg-next       │            │ sync.rs              │
  │ decode video+audio│──video──►  │ compare frame.pts    │
  │                   │  channel   │ vs audio clock       │
  │ ascii.rs          │            │                      │
  │ convert to ASCII  │            │ renderer.rs          │
  │                   │──audio──►  │ draw to terminal     │
  └──────────────────┘  channel   └──────────────────────┘
                                          │
                                   ┌──────▼──────┐
                                   │ audio.rs     │
                                   │ AudioBridge  │
                                   │ → rodio Sink │
                                   └─────────────┘
Sync mechanism: Audio is the master clock. An AudioClock (backed by Arc<AtomicU64> counting consumed samples) tracks playback position. The renderer compares each frame's pts to the audio clock:

Frame too early → sleep
Frame too late → drop it
Frame on time → display it
Phased Implementation
Phase 1: The Silent Loop
Goal: Decode video frames, convert to ASCII, print to stdout at max speed.

Files: Cargo.toml, main.rs, cli.rs, error.rs, types.rs, decoder.rs (video-only), ascii.rs

cargo init --name cli-nema, configure Cargo.toml with clap, ffmpeg-next, anyhow, thiserror
Implement cli.rs — clap derive structs for play <FILE> --color --invert --width
Implement decoder.rs — open file, find video stream, decode frames via ffmpeg_next, resize + convert to RGB24 using libswscale
Implement ascii.rs — grayscale-only: map pixel luminance to " .:-=+*#%@", build full frame string
Wire up in main.rs: parse args → open decoder → loop decode → convert → println
Verify: cargo run --release -- play ./test.mp4 floods terminal with recognizable ASCII art.

Phase 2: The Renderer
Goal: Proper terminal UI — alternate screen, in-place rendering, quit on keypress.

Files: renderer.rs

Implement TerminalRenderer — EnterAlternateScreen, enable_raw_mode, Hide cursor
draw_frame() — MoveTo(0,0) + Print via BufWriter<Stdout> + single flush()
poll_quit() — non-blocking check for 'q', Esc, Ctrl+C
Drop impl — always restore terminal even on panic
Add naive wall-clock frame timing: sleep(1/fps) between frames
Verify: Video plays in-place, no scrollback pollution, 'q' exits cleanly, Ctrl+C restores terminal.

Phase 3: Audio & Sync
Goal: Synchronized audio/video playback.

Files: audio.rs, sync.rs, player.rs; extend decoder.rs for audio

Extend decoder.rs — find audio stream, create audio decoder + resampler (→ f32/44100Hz/stereo)
Implement AudioBridge in audio.rs — rodio::Source over crossbeam::Receiver<Vec<f32>> + AudioClock via Arc<AtomicU64>
Implement FrameSynchronizer in sync.rs — compare frame.pts vs audio_clock.elapsed(), return Display/Wait/Drop
Implement player.rs orchestrator — create channels (bounded(30) video, bounded(100) audio), spawn decoder thread, run renderer loop on main thread, start rodio Sink
Handle videos without audio: fall back to wall-clock Instant timer
Verify: Audio plays correctly, video is lip-synced, frame drops happen under load, no-audio videos work.

Phase 4: Polish
Goal: Color support, robustness, edge cases.

RGB color in ascii.rs — emit \x1b[38;2;R;G;Bm per character when --color is set; skip re-emitting for adjacent same-color pixels
Invert mode — swap the ASCII density string
Graceful shutdown — AtomicBool shutdown flag checked by both threads; signal handler sets it
Edge cases — friendly errors for missing files, no video stream, tiny terminals
Performance profiling — target stable 30fps, CPU < 50%
Verify: Color output works in TrueColor terminals, all quit paths restore terminal, test with mp4/mkv/webm formats.

Key Pitfalls to Watch
Risk	Severity	Mitigation
FFmpeg system lib linkage	HIGH	Document exact apt install command; test on fresh system early
ffmpeg-next version vs system FFmpeg mismatch	MEDIUM	Use v7.0 for broad compat; detect via pkg-config
Color mode terminal performance (~5.7MB/s stdout at 30fps)	MEDIUM	BufWriter, skip redundant color codes, default to grayscale
Audio buffer underrun (crackling)	MEDIUM	Generous channel capacity; prioritize audio packets
Thread deadlocks on shutdown	LOW	Dropping Sender unblocks Receiver; Drop impl on renderer
Verification Checklist
 Phase 1: ASCII output is recognizable from a known video
 Phase 2: Terminal restores cleanly on all exit paths (q, Esc, Ctrl+C, panic)
 Phase 3: Audio/video desync < 100ms (test with clapper-board video)
 Phase 3: Videos without audio play at correct speed
 Phase 4: Color mode works in kitty/alacritty/iTerm2
 Phase 4: Stable 30fps on 1080p video, CPU < 50% in release mode
 Phase 4: Multiple formats work (mp4, mkv, webm)