
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int mostWordsFound(vector<string> &sentences)
    {
        int maxSpaces = 0;
        for (int i = 0; i < sentences.size(); i++)
        {
            int sumSpaces = 0;
            for (const char &c : sentences[i])
            {
                if (c == ' ')
                    sumSpaces++;
            }
            maxSpaces = max(maxSpaces, sumSpaces);
        }
        return maxSpaces + 1;
    }
};
int main()
{
}