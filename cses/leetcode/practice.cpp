#include <bits/stdc++.h>
using namespace std;
struct node{
    int val;
    int level;
};
class Solution {
public:  
    int minimumOperationsToMakeEqual(int x, int y) {
        set<int> visit;
        queue<node>q;
        q.push({x,0});
        while(q.empty()==false){
            struct node t = q.front();
            q.pop();
            if(y==t.val)return t.level;
            visit.insert(t.val);
            if(t.val % 5 == 0){
                if(visit.find(t.val/5) == visit.end()){
                    q.push({t.val/5, t.level+1});
                }
            }
            if(t.val % 11 == 0){
                if(visit.find(t.val/11) == visit.end()){
                    q.push({t.val/11, t.level+1});
                }
            }
            if(true){
                if(visit.find(t.val + 1) == visit.end()){
                    q.push({t.val + 1, t.level+1});
                }
            }
            if(true){
                if(visit.find(t.val -1 ) == visit.end()){
                    q.push({t.val -1, t.level+1});
                }
            }
        }
        return -100;
    }
};