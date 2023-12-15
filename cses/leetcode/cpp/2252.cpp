// use prefix sum computation to calculate the total flowers booming at ith time-index

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people)
    {
        int maxTime = 0;
        for (auto flower : flowers)
        {
            maxTime = max(flower[1] + 1, maxTime);
        }
        vector<int> t(maxTime + 1, 0); // total blooming flowers
        for (auto flower : flowers)
        {
            t[flower[0]] += 1;
            maxTime = max(flower[1] + 1, maxTime);
            t[flower[1] + 1] += -1;
        }
        for (int i = 1; i < maxTime; i++)
        {
            t[i] += t[i - 1];
        }
        vector<int> results;
        for (auto p : people)
        {
            results.push_back(t[p]);
        }
        return results;
    }
};
int main()
{
}
