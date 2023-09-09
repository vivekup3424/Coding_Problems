// 763. Partition Labels
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> partitionLabels(string s)
    {
        vector<int> ans;
        int n = s.size();
        int i = 0, j = n - 1;
        int sum = 0;
        while (sum < n)
        {
            if (s[i] == s[j])
            {
                ans.push_back(j - i + 1);
                sum += j - i + 1;
                i = j + 1;
                j = n - 1;
            }
            else
            {
                j--;
            }
        }
        return ans;
    }
};
int main()
{
}