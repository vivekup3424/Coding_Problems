#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxScoreSightseeingPair(vector<int> &values)
    {
        int n = values.size();
        int maxi = -1, maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (values[i] >= maxi)
            {
                maxi = values[i];
                maxIndex = i;
            }
        }
        int second = INT_MIN, secondIndex = -1;
        for (int j = 0; j < n; j++)
        {
            if (j != maxIndex)
            {
                if (values[j] + (maxIndex - j) > second)
                {
                    second = values[j] + min((maxIndex - j), (j - maxIndex));
                    secondIndex = j;
                }
            }
        }
        return maxi + second;
    }
};
int main()
{
    vector<int> values = {9, 7, 6, 7, 6, 9};
    Solution().maxScoreSightseeingPair(values);
}