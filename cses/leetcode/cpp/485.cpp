// use sliding window for this
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int findMaxConsecutiveOnes(std::vector<int> &nums)
    {
        int max_length = 0;
        int current_length = 0;

        for (int num : nums)
        {
            if (num == 1)
            {
                current_length++;
                max_length = std::max(max_length, current_length);
            }
            else
            {
                current_length = 0;
            }
        }

        return max_length;
    }
};
int main()
{
}