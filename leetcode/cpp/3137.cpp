#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumOperationsToMakeKPeriodic(string word, int k)
    {
        int length = k;
        int minCount = INT_MAX;
        while (length < k)
        {
            map<string, int> freq;
            int n = word.size();
            for (int i = 0; i < n; i++)
            {
                if (i % k == 0)
                {
                    string temp = word.substr(i, length);
                    freq[temp]++;
                }
            }
            // printing the map, and getting the substring with
            // highest frequency
            string max_substr = "";
            int max_freq = 0;
            for (auto it : freq)
            {
                if (it.second > max_freq)
                {
                    max_substr = it.first;
                    max_freq = it.second;
                }
            }
            for (int i = 0; i < word.size(); i += length)
            {
            }
        }
    }
};
int main()
{
    string word = "leetcoleet";
    int k = 2;
    Solution A;
    A.minimumOperationsToMakeKPeriodic(word, k);
}