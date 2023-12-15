
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    int partitionString(string s)
    {
        int count = 0;
        unordered_set<char> set;
        for (int i = 0; i < s.size(); i++)
        {
            if (set.find(s[i]) != set.end())
            {
                set.clear();
                count++;
            }
            set.insert(s[i]);
        }
        if (!set.empty())
            count++;
        return count;
    }
    // Time: O(n)
    // Space: O(n)
    // I think I cam improve the space complexity to O(1) by using a vector of size 26
};
int main()
{
    Solution1 s;
    cout << s.partitionString("ssssss") << endl;
    return 0;
}