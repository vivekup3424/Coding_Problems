
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> freq;
        for (auto c : s)
        {
            freq[c]++;
        }
        priority_queue<pair<int, char>> maxHeap;
        for (auto it : freq)
        {
            maxHeap.push({it.second, it.first});
        }
        string t;
        while (maxHeap.empty() == false)
        {
            pair<int, char> p = maxHeap.top();
            while (p.first--)
            {
                t.push_back(p.second);
            }

            maxHeap.pop();
        }
        return t;
    }
};
int main()
{
    Solution A = Solution();
    string s = "tree";
    string t = A.frequencySort(s);
    return 0;
}