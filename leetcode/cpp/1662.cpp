
#include <bits/stdc++.h>
using namespace std;
string resultant(vector<string> w1)
{
    string r;
    for (auto str : w1)
    {
        r += str;
    }
    return r;
}
class Solution
{
public:
    bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
    {
        string s1 = resultant(word1);
        string s2 = resultant(word2);
        return s1 == s2;
    }
};
int main()
{
}