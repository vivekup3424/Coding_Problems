
#include <bits/stdc++.h>
using namespace std;
// important revise this question
class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        // two pointer approach
        int i = 0, j = 0;
        while (i < nums.size())
        {
            if (nums[i] != val)
            {
                nums[j++] = nums[i++];
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
}
