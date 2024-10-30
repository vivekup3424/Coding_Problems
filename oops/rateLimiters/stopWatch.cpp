/**
 * - **Task**: Create a console-based stopwatch that starts timing when you press Enter, pauses/resumes on each subsequent Enter press, and stops timing on a specific key (e.g., 'q' for quit).
- **Skills Practiced**: Using `chrono` to measure elapsed time, handling user input, and managing pauses and resumes.
*/
#include <chrono>
#include <iostream>

int main() {
    bool is_paused = false;
    auto start_time = std::chrono::steady_clock::time_point();
    auto pause_start = std::chrono::steady_clock::time_point();
    std::chrono::steady_clock::duration paused_duration(0);

    char input;
    std::cout << "Press Enter to start/pause/resume the stopwatch, and 'q' to quit.\n";

    while (true) {
        input = std::cin.get();
        
        if (input == '\n') {
            if (start_time == std::chrono::steady_clock::time_point()) {
                // First Enter press - start the stopwatch
                start_time = std::chrono::steady_clock::now();
                std::cout << "Stopwatch started.\n";
            } else if (!is_paused) {
                // Pause the stopwatch
                pause_start = std::chrono::steady_clock::now();
                is_paused = true;
                std::cout << "Stopwatch paused.\n";
            } else {
                // Resume the stopwatch
                paused_duration += std::chrono::steady_clock::now() - pause_start;
                is_paused = false;
                std::cout << "Stopwatch resumed.\n";
            }
        } else if (input == 'q') {
            // Quit - calculate final elapsed time
            auto end_time = std::chrono::steady_clock::now();
            auto total_elapsed = end_time - start_time - paused_duration;
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(total_elapsed).count();
            
            std::cout << "Final elapsed time: " << elapsed_seconds << " seconds.\n";
            break;
        }

        // Display elapsed time while running
        if (!is_paused && start_time != std::chrono::steady_clock::time_point()) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed_time = current_time - start_time - paused_duration;
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count();
            std::cout << "Elapsed time: " << elapsed_seconds << " seconds\r" << std::flush;
        }
    }

    return 0;
}
