#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countPairs(vector<int> &nums)
    {
        int n = nums.size();
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[i] == nums[j])
                {
                    count++;
                    continue; // Directly continue as these are exactly equal
                }
                string s = to_string(nums[i]);
                string t = to_string(nums[j]);
                if (s.size() != t.size())
                {
                    continue;
                }
                vector<int> v;
                for (int i = 0; i < s.size(); i++)
                {
                    if (s[i] != t[i])
                    {
                        v.push_back(i);
                    }
                }
                if (v.size() != 2)
                {
                    continue;
                }
                string s1 = s, s2 = s, t1 = t, t2 = t;
                swap(s1[v[0]], s1[v[1]]);
                swap(t2[v[0]], t2[v[0]]);
                int l1 = stoi(s1);
                int r1 = stoi(t1);
                int l2 = stoi(s2);
                int r2 = stoi(t2);
                cout << "l1" << l1 << endl;
                cout << "r1" << r1 << endl;
                cout << "l2" << l2 << endl;
                cout << "r2" << r2 << endl;
                if (l1 == r1 || l2 == r2)
                {
                    count++;
                    continue;
                }
            }
        }
        return count;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {3, 12, 30, 17, 21};
    cout << sol.countPairs(nums) << endl; // Output should be 2
    return 0;
}
