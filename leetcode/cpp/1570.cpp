
#include <bits/stdc++.h>
using namespace std;
class SparseVector
{
public:
    vector<int> nums;
    SparseVector(vector<int> nums)
    {
        this->nums = nums;
    }
    int dotProduct(vector<int> vec)
    {
        int res = 0;
        int n = this->nums.size();
        for (int i = 0; i < n; i++)
        {
            if (vec[i] != 0 and nums[i] != 0)
            {
                res += nums[i] * vec[i];
            }
        }
        return res;
    }
};
int main()
{
}