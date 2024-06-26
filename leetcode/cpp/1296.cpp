#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution
{
public:
    bool isPossibleDivide(vector<int> &nums, int k)
    {
        int n = nums.size();
        if (n % k != 0)
        {
            return false;
        }
        map<int, int> freqHashMap;
        for (auto h : nums)
        {
            freqHashMap[h]++;
        }
        // let's use map for searching, that way my
        // time complexity would be reduced to O(logn) for searching
        bool flag = true;
        for (auto it : freqHashMap)
        {
            while (it.second > 0)
            {
                for (int i = 0; i < k; i++)
                {
                    int element = it.first + i;
                    if (freqHashMap.find(element) != freqHashMap.end())
                    {
                        if (freqHashMap[element] == 0)
                        {
                            flag = false;
                            return flag;
                        }
                        else
                        {
                            freqHashMap[element]--;
                        }
                    }
                    else
                    {
                        flag = false;
                        return flag;
                    }
                }
            }
        }
        return true;
    }
};
int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 6};
    int k = 4;
    cout << Solution().isPossibleDivide(nums, k) << endl;
    return 0;
}
