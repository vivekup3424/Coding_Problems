
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies)
    {
        int presentMax = 0;
        for (auto candy : candies)
            presentMax = max(presentMax, candy);
        vector<bool> ans;
        for (int i = 0; i < candies.size(); i++)
        {
            if (candies[i] + extraCandies >= presentMax)
                ans.push_back(true);
            else
                ans.push_back(false);
        }
        return ans;
    }
};
int main()
{
}