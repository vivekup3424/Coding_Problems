
#include <bits/stdc++.h>
using namespace std;
int majEl(vector<int> &nums)
{
    int count = 0;
    int res = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (!count)
            res = nums.size();
        nums[i] == res ? count++ : count--;
    }
    return res;
}
int main()
{
}