
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int atmost(vector<int> &A, int B)
    {
        int l = 0, r = 0, count = 0;
        unordered_map<int, int> mp;
        while (r < A.size())
        {
            mp[A[r]]++;
            while (mp.size() > B)
            {
                unordered_map<int, int>::iterator it = mp.find(A[l]); // find the leftmost element to remove
                it->second--;
                if (it->second == 0)
                {
                    mp.erase(it);
                }
                l++; // after erasing increment the pointer
            }
            count += (r - l + 1);
            r++;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int> &A, int B)
    {
        // number of subarrays with at most k distinct elements - number of subarrays with at most k-1 distinct elements
        return atmost(A, B) - atmost(A, B - 1);
    }
};
int main()
{
}