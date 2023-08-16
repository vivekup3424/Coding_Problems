#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minSwap(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        vector<int> swap(n, n), keep(n, n);

        swap[0] = 1;
        keep[0] = 0;

        for (int i = 1; i < n; i++)
        {
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1])
            {
                keep[i] = keep[i - 1];
                swap[i] = swap[i - 1] + 1;
            }
            if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1])
            {
                keep[i] = min(keep[i], swap[i - 1]);
                swap[i] = min(swap[i], keep[i - 1] + 1);
            }
        }

        return min(swap[n - 1], keep[n - 1]);
    }
};

int main()
{
}