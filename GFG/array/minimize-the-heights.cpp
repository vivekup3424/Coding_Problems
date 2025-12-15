#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int getMinDiff(vector<int> &arr, int k)
    {
        int minValue = *min_element(arr.begin(), arr.end());
        int maxValue = *max_element(arr.begin(), arr.end());
        int midValue = (minValue + maxValue) / 2;
        vector<int> temp(arr.size());
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] <= midValue)
            {
                temp[i] = arr[i] - k;
            }
            else
            {
                temp[i] = arr[i] + k;
            }
        }
        minValue = *min_element(temp.begin(), temp.end());
        maxValue = *max_element(temp.begin(), temp.end());
        return maxValue - minValue;
    }
};