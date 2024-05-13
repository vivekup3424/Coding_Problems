#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maximumEnergy(vector<int> &energy, int k)
    {
        int n = energy.size();
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++)
        {
            int before = 0;
            if (i - k >= 0)
            {
                before = dp[i - k];
            }
            dp[i] = before + energy[i];
        }
        cout << "Out the dp" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << dp[i] << " ";
        }
        cout << endl;

        int max_value = *max_element(energy.end() - k, energy.end());
        return max_value;
    }
};