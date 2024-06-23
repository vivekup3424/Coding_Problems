#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        set<int> set1, set2;
        for (int i = 0; i < nums1.size(); i++)
        {
            set1.insert(nums1[i]);
        }
        for (int i = 0; i < nums2.size(); i++)
        {
            set2.insert(nums2[i]);
        }
        vector<int> v;
        for (auto c : set1)
        {
            if (set2.find(c) != set2.end())
                v.push_back(c);
        }
        return v;
    }
};
int main()
{
}