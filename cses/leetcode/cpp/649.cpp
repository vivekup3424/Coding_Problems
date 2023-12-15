
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string predictPartyVictory(string senate)
    {
        deque<int> R, D;
        for (int i = 0; i < senate.size(); i++)
        {
            if (senate[i] == 'R')
            {
                R.push_front(i);
            }
            else
            {
                D.push_front(i);
            }
        }
        int n = senate.size();
        while (R.empty() == false and D.empty() == false)
        {
            int rTurn = R.back();
            int dTurn = D.back();
            R.pop_back();
            D.pop_back();
            if (rTurn < dTurn)
            {
                R.push_front(rTurn + n);
            }
            else
            {
                D.push_front(dTurn + n);
            }
        }
        if (R.empty() == false)
        {
            return "Radiant";
        }
        else
            return "Dire";
    }
};
int main()
{
    string senate = "DDRRR";
    Solution A = Solution();
    A.predictPartyVictory(senate);
}