
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        map<int, int> frq;
        for (int i : nums)
        {
            frq[i]++;
        }
        int ans = 0;
        for (auto &a : frq)
        {
            if (a.second == 1)
                return -1;
            ans += a.second / 3;
            if (a.second % 3)
                ++ans;
        }
        return ans;
    }
};
int main()
{
}