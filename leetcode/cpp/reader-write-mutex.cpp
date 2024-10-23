#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex resourceMutex;       // Mutex for the shared resource (data)
std::mutex readCountMutex;      // Mutex for read_count updates
int read_count = 0;             // Number of active readers
int shared_data = 0;            // The shared resource (data) being read/written

void reader(int id) {
    while (true) {
        // Acquire lock to modify read_count
        {
            std::lock_guard<std::mutex> lock(readCountMutex);
            read_count++;
            if (read_count == 1) {  // If first reader, lock the shared resource for writing
                resourceMutex.lock();
            }
        }

        // Reading the shared resource
        cout << "Reader " << id << " is reading shared data: " << shared_data << endl;

        // Simulate reading time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Done reading
        {
            std::lock_guard<std::mutex> lock(readCountMutex);
            read_count--;
            if (read_count == 0) {  // Last reader unlocks the shared resource for writers
                resourceMutex.unlock();
            }
        }

        // Simulate some delay between reads
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id) {
    while (true) {
        // Lock the resourceMutex for writing
        resourceMutex.lock();

        // Writing to the shared resource
        shared_data = id;  // Example: writer modifies shared_data
        cout << "Writer " << id << " is writing shared data: " << shared_data << endl;

        // Simulate writing time
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Unlock the resourceMutex after writing
        resourceMutex.unlock();

        // Simulate some delay between writes
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    // Create reader and writer threads
    thread reader1(reader, 1);
    thread reader2(reader, 2);
    thread writer1(writer, 1);
    thread writer2(writer, 2);

    // Join threads to the main thread (keep them alive)
    reader1.join();
    reader2.join();
    writer1.join();
    writer2.join();

    return 0;
}

