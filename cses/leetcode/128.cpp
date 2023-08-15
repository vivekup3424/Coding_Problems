
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> s;
        for (auto n : nums)
        {
            s.insert(n);
        }
        int len = 0, maxLen = 0, start = 0;
        for (auto n : nums)
        {
            if (s.find(n - 1) == s.end())
            {
                start = n;
                len = 1;
                while (s.find(n + 1) != s.end())
                {
                    len++;
                    n++;
                }
                maxLen = max(len, maxLen);
            }
        }
        return maxLen;
    }
};
int main()
{
    // Example usage
    vector<int> nums = {100, 4, 200, 1, 3, 2, 5};
    Solution sol;
    int longest = sol.longestConsecutive(nums);
    cout << "Longest consecutive sequence: " << longest << endl;

    return 0;
}