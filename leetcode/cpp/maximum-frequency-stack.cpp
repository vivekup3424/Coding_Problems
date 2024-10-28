#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
class node{
public:
    int value;
    int cumulative_frequency;
    int timeOfInsertion;
    node(int v,int c,int t){
        value = v;
        cumulative_frequency = c;
        timeOfInsertion = t;
    }
};
class comparator{
public:
    bool operator()(const node &a, const node &b){
        if(a.cumulative_frequency > b.cumulative_frequency){
            return true; //maxHeap wrt frequency
        }else{
            return a.timeOfInsertion < b.timeOfInsertion; //minHeap wrt time
        }
    }
};
class FreqStack {
private:
    priority_queue<node,vector<node>,comparator> minHeap; //{element,cumulative frequency}
    unordered_map<int,int> freq;
    int time;
public:
    FreqStack() {
        time = 0;
    }
    
    void push(int val) {
        freq[val]++;
        minHeap.push({val,freq[val],time++});
    }
    
    int pop() {
        auto c = minHeap;
        while(c){
            printf("%d %d %d",)
        }
        auto temp = minHeap.top().value;
        freq[temp]--;
        minHeap.pop();
        return temp;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
