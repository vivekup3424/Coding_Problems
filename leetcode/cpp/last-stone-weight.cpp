#include <bits/stdc++.h>
#include <queue>
using namespace std;
class comparator{
public:
    bool operator()(int a, int b){
        return a < b;
    }
};
class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int,vector<int>,comparator> pq;
        for (int i = 0; i < stones.size(); i++)
        {
            pq.push(stones[i]);
        }
        while (pq.size() >= 2)
        {
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();
            int r = a == b ? 0 : abs(a - b);
            pq.push(r);
        }
        return pq.top();
    }
};
int main (int argc, char *argv[]) {
    return 0;
}
