/**
 * - **Task**: 
 *      Create a console-based stopwatch that starts timing when you press Enter, 
 *      pauses/resumes on each subsequent Enter press, and stops timing on a specific key 
 *      (e.g., 'q' for quit).
- **Skills Practiced**: 
        Using `chrono` to measure elapsed time, handling user input, 
        and managing pauses and resumes.
*/
#include <iostream>
#include <chrono>
using namespace std;
    
int main (int argc, char *argv[]) {
    const auto start_time = std::chrono::steady_clock::time_point();
    const auto pause_time = std::chrono::steady_clock::time_point();
    const auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end() - start);
    
    return 0;
}
