#include <condition_variable>
#include <mutex>
using namespace std;

#define MAX_SIZE 10;
//producers and consumers are reading and writing from a shared limited size buffer
// Solution using mutex and condition variables
mutex m, full, empty;
condition_variable cv;
queue<int> dataQueue;

void producer(){
  unique_lock<mutex> lock(m);

}

void con
