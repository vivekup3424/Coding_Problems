#include <condition_variable>
#include <mutex>
#include <queue>
using namespace std;

#define max_size 10
//producers and consumers are reading and writing from a shared limited size buffer
// solution using mutex and condition variables
class semaphore{
private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
public:
  semaphore(int a): count(a){}
  void setcount(int a){
    count = a;
  }
  void signal(){
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    if(count<=0){ //this means some threads would have been waiting
      cv.notify_one();
    }
  }
  void wait(){
    std::unique_lock<std::mutex> lock(mtx);
    count--;
    while(count<0){
      cv.wait(lock);
    }
  }
};
mutex m;
semaphore full(max_size);
semaphore empty(max_size);
condition_variable cv;
queue<int> dataqueue;

void producer(int a){
  unique_lock<mutex> lock(m);
  empty.wait();
  dataqueue.push(a);
  full.signal();
}
int consumer(){
  unique_lock<mutex> lock(m);
  full.wait();
  int a = dataqueue.front();
  dataqueue.pop();
  empty.signal();
  return a;
}


int main(){
  full.setcount(0);

  return 0;
}
