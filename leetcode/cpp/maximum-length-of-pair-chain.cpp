#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findLongestChain(vector<vector<int>> pairs)
    {
        sort(pairs.begin(), pairs.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });
        int current = INT_MIN, answer = 0;
        for(vector<int> pair: pairs){
            if(pair[0] > current){
                answer++;
                current = pair[1];
            }
        }
        return answer;
    }
};