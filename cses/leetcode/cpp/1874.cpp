
#include <bits/stdc++.h>
using namespace std;
int minProductSum(vector<int> &nums1, vector<int> &nums2)
{
    sort(nums1.begin(), nums2.end());
    sort(nums2.begin(), nums2.end(), greater<int>());
    int sum = 0;
    int n = nums1.size();
    for (int i = 0; i < n; i++)
    {
        sum += (nums1[i] * nums2[i]);
    }
    return sum;
}
int main()
{
}