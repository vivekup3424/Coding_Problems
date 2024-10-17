#include <condition_variable>
#include <functional>
#include <mutex>
using namespace std;
class FizzBuzz {
private:
    int n;
    condition_variable cv;
    mutex m;
    int count = 0;
public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        unique_lock<mutex> lock(m);
        while(!(count % 3 == 0 and count % 5 != 0)){
            cv.wait(lock);
        }
        printFizz();
        count++;
        cv.notify_all();
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        unique_lock<mutex> lock(m);
        while(!(count % 5 == 0 and count % 3 != 0)){
            cv.wait(lock);
        }
        printBuzz();
        count++;
        cv.notify_all();
        
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        unique_lock<mutex> lock(m);
        while(!(count % 5 == 0 and count % 3 == 0)){
            cv.wait(lock);
        }
        printFizzBuzz();
        count++;
        cv.notify_all();

    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        unique_lock<mutex> lock(m);
        while(!(count % 5 != 0 and count % 3 != 0)){
            cv.wait(lock);
        }
        printNumber(count);
        count++;
        cv.notify_all();

    }
};
