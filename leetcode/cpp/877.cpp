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
        if (turn == 0)
        {
            return piles[i];
        }
        else
        {
            return 0;
        }
    }
    if (turn == 0)
    {
        return max(piles[i] + recurse(piles, i + 1, j, 1 - turn),
                   piles[j] + recurse(piles, i, j - 1, 1 - turn));
    }
    else
    {
        return min(recurse(piles, i + 1, j, 1 - turn), recurse(piles, i, j - 1, 1 - turn));
    }
}
bool stoneGameRecursive(vector<int> piles)
{
    cout << "Sum = " << recurse(piles, 0, piles.size() - 1, 0);
    return true;
}

int main()
{
    vector<int> piles = {3, 2, 10, 4};
    stoneGameRecursive(piles);
}