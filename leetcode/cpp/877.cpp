#include <bits/stdc++.h>
using namespace std;
// Method 1:- Wrong solution, think of game theory
class Solution
{
public:
    bool stoneGame(vector<int> &piles)
    {
        int sum1 = 0, sum2 = 0; // sum1 = Alice
        int n = piles.size();
        int i = 0, j = n - 1;
        while (i < j)
        {
            if (piles[i] > piles[j])
            {
                sum1 += piles[i++];
            }
            else
            {
                sum1 += piles[j--];
            }
            if (i <= j)
            {
                if (piles[i] > piles[j])
                {
                    sum2 += piles[i++];
                }
                else
                {
                    sum2 += piles[j--];
                }
            }
        }
        return sum1 > sum2;
    }
};
int recurse(vector<int> &piles, int i, int j, int turn)
{
    if (i > j)
    {
        return 0;
    }
    else if (i == j)
    {
        return piles[i];
    }
    if (turn == 0)
    {
        return max(piles[i] + recurse(piles, i + 1, j, !turn),
                   piles[j] + recurse(piles, i, j - 1, !turn));
    }
    else if (turn == 1)
    {
        return min(piles[i] + recurse(piles, i + 1, j, !turn),
                   piles[j] + recurse(piles, i, j - 1, !turn));
    }
}
int recurse(vector<int> &piles, int i, int j, int turn)
{
    if (i > j)
    {
        return 0;
    }
    else if (i == j)
    {
        return piles[i];
    }
    if (turn == 0)
    {
        return max(piles[i] + recurse(piles, i + 1, j, !turn),
                   piles[j] + recurse(piles, i, j - 1, !turn));
    }
    else if (turn == 1)
    {
        return min(piles[i] + recurse(piles, i + 1, j, !turn),
                   piles[j] + recurse(piles, i, j - 1, !turn));
    }
}

int main()
{
    vector<int> piles = {3, 2, 10, 4};
    Solution A;
    A.stoneGame(piles);
}