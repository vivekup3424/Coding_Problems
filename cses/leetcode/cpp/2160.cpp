
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    int minimumSum(int num)
    {
        vector<int> nums;
        while (num > 0)
        {
            nums.push_back(num % 10);
            num = num / 10;
        }
        sort(nums.begin(), nums.end());
        int n1 = nums[0] * 10 + nums[3];
        int n2 = nums[1] * 10 + nums[2];
        return n1 + n2;
    }
};
class Solution
{
public:
    int minimumSum(int num)
    {
        string s = to_string(num);
        sort(s.begin(), s.end());
        int res = 10 * (s[0] - '0') + 10 * (s[1] - '0') + (s[2] - '0') + (s[3] - '0');
        return res;
    }
};
int main()
{
}