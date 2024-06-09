#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int maximumLength(vector<int> &nums, int k)
    {
        int n = nums.size();
        // using sliding window approach
        int start = 0, end = 0;
        int length = 0, maxLength = 0, pair = 0;
        while (end < n)
        {
            while (pair > k and end < n and start < end)
            {
                if (nums[start] != nums[start + 1])
                {
                    pair--;
                }
                start++;
                length--;
                if (length < 0)
                {
                    length == 0;
                }
            }
            if (nums[end] == nums[end - 1] || (end == 0))
            {
                length++;
                end++;
            }
            else if (nums[end] != nums[end - 1])
            {
                length++;
                pair++;
                end++;
            }
            maxLength = max(maxLength, length);
        }
        return maxLength;
    }
};

int main()
{
    Solution A;
    vector<int> v = {1, 2, 3, 4, 5, 1};
    int k = 2;
    int ans = A.maximumLength(v, k);
    cout << ans << endl;
}