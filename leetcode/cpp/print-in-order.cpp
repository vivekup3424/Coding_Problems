#include <bits/stdc++.h>
#include <condition_variable>
#include <mutex>
#include <semaphore>
#include <functional>
using namespace std;
class Foo {
private:
    mutex m;
    condition_variable cv;
    int count;
public:
    Foo(): count(1) {
        
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lock(m);
        count++;
        printFirst();
        cv.notify_all(); //cv unlocks the lock by itself
        
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);
        while(count != 2){
            cv.wait(lock);
        }
        printSecond();
        count++;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        
        unique_lock<mutex> lock(m);
        while(count != 3){
            cv.wait(lock);
        }
        printThird();
        //we dont need to specifically unlock the lock here
        //as when the scope of this function get's over 
        //the lock get's unlocked
    }
};
class FooMutex{
private:
    mutex m, b, c;
public:
    FooMutex(){
        b.lock();
        m.lock();
    }
    void first(function<void()> printFirst){
        unique_lock<mutex> lock(m);
        printFirst();
        b.unlock();
    }
    void second(function<void()> printSecond){
        unique_lock<mutex> lock(b); //waits for first to unlock b
        printSecond();
        c.unlock();
    }
    void third(function<void()> printThird){
        unique_lock<mutex> lock(c);
        printThird();
    }
};

class FooSemaphore{
private:
    binary_semaphore b{0};
    binary_semaphore c{0};
    mutex m;
public:
    void first(function)
}
