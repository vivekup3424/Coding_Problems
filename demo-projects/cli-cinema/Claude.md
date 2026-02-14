Here is a streamlined Product Requirements Document (PRD) tailored for a solo developer building this in **Rust**.

---

# Product Requirements Document (PRD)
**Project Name:** `cli-nema` (CLI Cinema)
**Language:** Rust
**Version:** 0.1.0 (MVP)

## 1. Executive Summary
`cli-nema` is a high-performance command-line tool that renders video files as ASCII art in real-time. It synchronizes the visual output with the video’s audio track, providing a seamless viewing experience purely within the terminal emulator.

## 2. User Experience (UX)
### 2.1 User Flow
1.  The user opens a terminal.
2.  The user runs the command: `clinema play ./movie.mp4 --color`.
3.  The terminal clears. The video begins playing immediately with audio.
4.  The user sees the video rendered in ASCII characters.
5.  Pressing `q` or `Esc` stops playback and restores the terminal.

### 2.2 CLI Interface
```bash
clinema <COMMAND> [OPTIONS]

COMMANDS:
  play <FILE_PATH>    Plays the video file.

OPTIONS:
  -c, --color         Enable TrueColor (RGB) rendering (default: grayscale).
  -i, --invert        Invert the ASCII brightness map (for light mode terminals).
  -w, --width <INT>   Force a specific width (default: auto-detect).
```

## 3. Functional Requirements
*   **Video Decoding:** Must support common formats (.mp4, .mkv) via `ffmpeg` or `opencv` bindings.
*   **Audio Playback:** Must extract audio and play it in sync with the visual feed.
*   **Frame skipping:** If the rendering lags behind the audio, the player must drop video frames to catch up.
*   **Resizing:** The ASCII output must respect the terminal window dimensions and aspect ratio.
*   **Grayscale Map:** Map pixel luminance to a standard ASCII density string (e.g., ` .:-=+*#%@`).

## 4. Technical Specifications (Rust)

### 4.1 Recommended Crate Stack
*   **Argument Parsing:** `clap` (Standard, derive features).
*   **Video/Image Decoding:** `opencv` (Easier to implement frame grabbing than raw ffmpeg bindings) OR `ffmpeg-next` (Steeper learning curve but more control).
*   **Image Processing:** `image` (For fast resizing/filtering if not using OpenCV's internal functions).
*   **Audio:** `rodio` (Easy, pure Rust audio playback).
*   **Terminal I/O:** `crossterm` (Lightweight, handles raw mode, cursor movement, and RGB colors better than ncurses).
*   **Concurrency:** `crossbeam` (For high-performance channels between decoder and renderer threads).

### 4.2 Architecture (The "Game Loop" Pattern)
The application will run on **two primary threads** (Producer/Consumer model) to prevent I/O blocking.

**Thread A: The Decoder (Producer)**
1.  Reads the video file using `opencv`.
2.  Resizes the frame to the target console width/height.
3.  Processes the frame into an ASCII string (with ANSI color codes if enabled).
4.  Pushes the processed string + timestamp into a `crossbeam::bounded` channel.

**Thread B: The Renderer (Consumer/Main)**
1.  Starts the Audio stream (`rodio`).
2.  Enters a loop:
    *   Checks `audio_stream.elapsed()`.
    *   Peek at the next frame in the channel.
    *   **Logic:**
        *   If `frame.time > audio.time`: Sleep (wait for audio to catch up).
        *   If `frame.time < audio.time - threshold`: Drop frame (we are lagging).
        *   If `frame.time ~= audio.time`: Print frame to stdout using `crossterm::Queue`.
3.  Flushes stdout buffer once per frame (buffered I/O is critical for performance).

### 4.3 Key Algorithms
**Aspect Ratio Correction:**
Terminal characters are roughly 2x as tall as they are wide.
```rust
// Pseudo-code for resizing logic
let target_width = terminal_width;
let aspect_ratio = video_width / video_height;
// Multiply height by ~0.55 to account for rectangular font glyphs
let target_height = (target_width / aspect_ratio) * 0.55; 
```

**ASCII Mapping (Grayscale):**
```rust
const ASCII_CHARS: &[u8] = b" .:-=+*#%@";
// Calculate index based on pixel brightness (0-255)
let index = (pixel_brightness as usize * (ASCII_CHARS.len() - 1)) / 255;
let char = ASCII_CHARS[index] as char;
```

## 5. Development Milestones
*   **Phase 1 (The Silent Loop):**
    *   Set up `clap`.
    *   Get `opencv` to read a file.
    *   Convert one frame to ASCII and print it.
    *   Loop through all frames (no timing, just max speed).
*   **Phase 2 (The Renderer):**
    *   Integrate `crossterm`.
    *   Implement "Alternate Screen" (prevents scrollback clutter).
    *   Implement cursor repositioning `MoveTo(0,0)` instead of `clear`.
*   **Phase 3 (The Audio & Sync):**
    *   Add `rodio` to play the audio track of the file.
    *   Implement the Master Clock logic (drop frames if video lags audio).
*   **Phase 4 (Polish):**
    *   Add RGB color support.
    *   Handle `Ctrl+C` gracefully to restore cursor/terminal state.

## 6. Success Metrics
*   **FPS:** Stable 30FPS on a standard 1080p video resized to terminal.
*   **CPU Usage:** Should remain under 50% on a modern core (efficient loop).
*   **Sync:** Audio/Video desync should not be noticeable to the human eye (< 100ms drift).