#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct node{
    int x;
    int y;
    node(int a, int b):x(a),y(b){}
};
class comparator{
public:
    bool operator()(pair<int,node*> &a, pair<int,node*> &b){
        return a->first > b->first;
    }
};
bool compare(pair<int,node*> &a, pair<int,node*> &b){
    return a.first > b.first ;
}
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        priority_queue<pair<int,node*>, vector<pair<int,node*>>, bool(pair<int,node*> &a, pair<int,node*> &b){}>pq(compare);
        set<node*> visitedSet;
        map<node*, int> distance;
        return 0;
    }
};
