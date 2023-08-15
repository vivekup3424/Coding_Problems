
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies)
    {
        // find the maxcandies any kid currently has
        auto m = max_element(candies.begin(), candies.end());
        int M = *m;
        // find the maxCandies vector
        int n = candies.size();
        vector<int> maxCandies(n);
        for (int i = 0; i < n; i++)
        {
            maxCandies[i] = candies[i] + extraCandies;
        }
        vector<bool> result(n);
        for (int i = 0; i < n; i++)
        {
            result[i] = (maxCandies[i] >= M);
        }
        return result;
    }
};
int main()
{
}