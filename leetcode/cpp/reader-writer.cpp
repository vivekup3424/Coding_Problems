#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    semaphore(int a) : count(a) {}

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        if (count <= 0) {  // Notify if there are waiting threads
            cv.notify_one();
        }
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        count--;
        while (count < 0) {
            cv.wait(lock);  // Wait until signaled
        }
    }
};

std::mutex resourceMutex;       // Mutex for the shared resource
semaphore rw_mutex(1);          // Semaphore for writers (ensures mutual exclusion for writing)
int read_count = 0;             // Keeps track of the number of active readers
semaphore mutex(1);             // Semaphore to ensure mutual exclusion when updating read_count
int shared_data = 0;            // The shared resource (data) being read/written

void reader(int id) {
    while (true) {
        mutex.wait();  // Lock to modify read_count
        read_count++;
        if (read_count == 1) {
            rw_mutex.wait();  // First reader locks the writers
        }
        mutex.signal();  // Release lock on read_count

        // Reading the shared resource
        cout << "Reader " << id << " is reading shared data: " << shared_data << endl;

        // Simulate reading time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Reader done
        mutex.wait();  // Lock to modify read_count
        read_count--;
        if (read_count == 0) {
            rw_mutex.signal();  // Last reader unlocks the writers
        }
        mutex.signal();  // Release lock on read_count

        // Simulate some delay between reads
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id) {
    while (true) {
        rw_mutex.wait();  // Lock to ensure mutual exclusion for writing

        // Writing to the shared resource
        shared_data = id;  // Example: writer modifies shared_data
        cout << "Writer " << id << " is writing shared data: " << shared_data << endl;

        // Simulate writing time
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        rw_mutex.signal();  // Unlock after writing

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

    // Join threads to main thread (keep them alive)
    reader1.join();
    reader2.join();
    writer1.join();
    writer2.join();

    return 0;
}

