// 4. Median of Two Sorted Arrays

#include <bits/stdc++.h>
using namespace std;

int main()
{
}
class Solution
{
public:
    void findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int n1 = nums1.size(), n2 = nums2.size();
        int total = n1 + n2;
        int half = total / 2;
        int left = 0, right = n1 - 1; // doing binary search on A
        int i = (left + right) / 2;
    }
};