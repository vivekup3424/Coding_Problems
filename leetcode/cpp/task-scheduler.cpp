#include <bits/stdc++.h>
#include <queue>
using namespace std;
class Node{
    public:
    char task;
    int time;
    Node(char A, int t): task(A), time(t){}
};
class comparator{
public:
    bool operator()(Node &A, Node &B){
        return A.time > B.time; //minheap
    }
};

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<bool> indices(10001,0);
        vector<int> timeAssigned(26,0);
        sort(tasks.begin(),tasks.end());
        priority_queue<*Node, vector<*Node>, comparator> minHeap;
        for(auto t : tasks){
            if(timeAssigned[t- 'A']==0){
                for(int i = 0; i < 10001; i++){
                    if(indices[i]==0){
                        timeAssigned[i - 'A'] = i;
                        auto newNode = new Node(t,i);
                        minHeap.push(newNode);
                    }
                }
            }
        }
    }
};
