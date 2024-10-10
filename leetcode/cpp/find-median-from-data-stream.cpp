#include <bits/stdc++.h>
#include <queue>
using namespace std;

class MedianFinder {
private:
    priority_queue<int>firstHalf;
    priority_queue<int,vector<int>,greater<int>> secondHalf;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        secondHalf.push(num);
        if(firstHalf.size()>0 and secondHalf.size()>0){
            if(firstHalf.top() > secondHalf.top()){
                int firstTop = firstHalf.top();
                firstHalf.pop();
                int secondTop = secondHalf.top();
                secondHalf.pop();
                firstHalf.push(secondTop);
                secondHalf.push(firstTop);
            }
        }
        if(secondHalf.size() > firstHalf.size()){
            int secondTop = secondHalf.top();
            secondHalf.pop();
            firstHalf.push(secondTop);
        }
    }
    
    double findMedian() {
        if(firstHalf.size()>secondHalf.size()){
            return (double)firstHalf.top();
        }
        else{
            return (double)((double)firstHalf.top() + (double)secondHalf.top())/2;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
