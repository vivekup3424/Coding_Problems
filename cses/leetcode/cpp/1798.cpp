#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int getMaximumConsecutive(vector<int> &coins)
    {
        sort(coins.begin(), coins.end());
        int smallestNumber = 0;
        int n = coins.size();
        for (int i = 0; i < n; i++)
        {
            if (smallestNumber >= (coins[i] - 1))
            {
                smallestNumber += coins[i];
            }
        }
        cout << smallestNumber + 1 << endl;
        return smallestNumber + 1;
    }
};