#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string shiftingLetters(string s, vector<vector<int>> shifts)
    {
        int n = s.size();
        vector<int> totalShift(n, 0);
        for (int i = 0; i < shifts.size(); i++)
        {
            int firstIdx = shifts[i][0];
            int lastIdx = shifts[i][1];
            int direction = (shifts[i][2] == 1 ? 1 : -1);
            totalShift[firstIdx] += direction;
            if (lastIdx + 1 < n)
            {
                totalShift[lastIdx + 1] -= direction;
            }
        }
        for (int i = 1; i < n; i++)
        {
            totalShift[i] += totalShift[i - 1];
        }
        for (int j = 0; j < n; j++)
        {
            int val = s[j] - 'a';
            int shiftedVal = (totalShift[j] + val + 26) % 26; // normalize the neg vals
            s[j] = 'a' + shiftedVal;
        }
        return s;
    }
};