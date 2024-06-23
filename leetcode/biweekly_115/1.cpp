
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> lastVisitedIntegers(vector<string> &words)
    {
        vector<int> values;
        vector<int> results;
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] != "prev")
            {
                int n = stoi(words[i]);
                values.push_back(n);
            }
            else
            {
                int j = values.size() - 1;
                while (i < words.size())
                {
                    if (words[i] == "prev")
                    {
                        if (j >= 0)
                        {
                            results.push_back(values[j]);
                        }
                        else
                        {
                            results.push_back(-1);
                        }
                        i++;
                        j--;
                    }
                    else
                    {
                        i--;
                        break;
                    }
                }
            }
        }
        return results;
    }
};
int main()
{
    vector<string> words = {"1",
                            "prev",
                            "2",
                            "prev",
                            "prev"};
    Solution A = Solution();
    vector<int> res = A.lastVisitedIntegers(words);
}