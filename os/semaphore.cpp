#include <condition_variable>
#include <mutex>
class Semaphore{
private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
public:
  Semaphore(int a): count(a){}
  void setCount(int a){
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
