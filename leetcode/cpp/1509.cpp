#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minDifference(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n <= 3)
        {
            return 0;
        }
        // take two choices
        // 1.Either convert the three largest elment the the smallest elemet
        // 2.Either convert the three smallest elements to the largest one
        // and then get the difference

        vector<int> temp1 = nums;
        vector<int> temp2 = nums;
        // choice1
        sort(temp1.begin(), temp1.end());
        int smallest = temp1[0];
        for (int i = 1; i <= 3; i++)
        {
            temp1[n - i] = smallest;
        }
        sort(temp1.begin(), temp1.end());
        int diff1 = temp1[n - 1] - temp1[0];

        sort(temp2.begin(), temp2.end());
        int largest = temp2[n - 1];
        for (int i = 0; i < 3; i++)
        {
            temp2[i] = largest;
        }
        sort(temp2.begin(), temp2.end());
        int diff2 = temp2[n - 1] - temp2[0];
        return min(diff1, diff2);
    }
};
