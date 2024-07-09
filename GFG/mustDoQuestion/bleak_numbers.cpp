
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int is_bleak(int n)
    {
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            int sum = mid + __popcount(mid);
            if (sum == n)
            {
                return n;
            }
            else if (sum > n)
            {
                r = mid - 1;
            }
            vector<int> v;
            else
            {
                l = mid + 1;
            }
        }
    }
};
int main()
{
}
