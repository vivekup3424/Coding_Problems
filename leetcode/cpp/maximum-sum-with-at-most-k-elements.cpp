#include <bits/stdc++.h>
using namespace std;
class Comparator{
    public:
    bool operator()(pair<int,int> &a, pair<int,int> &b){
        return a.first < b.first;
    }
};
class Solution
{
public:
    long long maxSum(vector<vector<int>> &grid, vector<int> &limits, int k)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, Comparator> maxHeap;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                maxHeap.push({grid[i][j],i});
            }
        }
        int maxSum = 0;
        int counter = 0;
        while(maxHeap.size()>0 and counter < k){
            auto [val,idx] = maxHeap.top();
            maxHeap.pop();
            if(limits[idx]>0){
                maxSum += val;
                limits[idx]-=1;
                counter+=1;
            }
        }
        return maxSum;
    }
};