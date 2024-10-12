
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int coinChange(vector<int> &coins, int a)
    {
        sort(coins.rbegin(), coins.rend());
        int count = 0;
        int i = 0;
        while (i < coins.size() and a)
        {
            count += a / coins[i];
            a = a % coins[i];
            i++;
        }
        if (a != 0)
            return -1;
        return count;
    }
};
int main()
{
    Solution solution;
    vector<int> coins = {186, 419, 83, 408};
    int amount = 6249;

    int result = solution.coinChange(coins, amount);

    cout << "Minimum number of coins needed: " << result << endl;

    return 0;
}
