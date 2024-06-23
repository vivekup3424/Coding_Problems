
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int start = 0, sum = 0, minLength = INT_MAX, current_length = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            current_length++;
            while (sum >= target)
            {
                minLength = min(minLength, current_length);
                sum -= nums[start];
                start++;
                current_length--;
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }
};
int main()
{
}