
#include <bits/stdc++.h>
using namespace std;
// Method 1 : Picking the highest 2 piles and 1 lowest pile, so that I get the second highest pile.
class Solution
{
public:
    int maxCoins(vector<int> &piles)
    {
        sort(piles.begin(), piles.end());
        int n = piles.size();
        int result = 0;
        for (int i = n - 2; i >= n / 3; i -= 2)
        {
            result += piles[i];
        }
        return result;
    }
};
int main()
{
}