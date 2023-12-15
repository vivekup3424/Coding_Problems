// 80. Remove Duplicates from Sorted Array II
//?
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1 || n == 2)
        {
            return n;
        }
        int i = 2, j = 2;
        while (i < n)
        {
            if (nums[i] != nums[i - 2])
            {
                nums[j] = nums[i++];
                j += 2;
            }
            else
            {
                i++;
            }
        }
        return j;
    }
};
void printVector(vector<int> nums)
{
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;
};
int main()
{
    vector<int> v = {1, 1, 1, 2, 2, 3};
    Solution *A = new Solution();
    A->removeDuplicates(v);
    printVector(v);
}
