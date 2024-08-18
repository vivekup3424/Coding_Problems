#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long maxEnergyBoost(vector<int> &energyDrinkA, vector<int> &energyDrinkB)
    {
        int n = energyDrinkA.size();
        vector<long long> pref_A(n, 0);
        vector<long long> pref_B(n, 0);
        vector<long long> suff_A(n, 0);
        vector<long long> suff_B(n, 0);
        for (int i = 1; i < n; i++)
        {
            pref_A[i] = pref_A[i - 1] + energyDrinkA[i - 1];
            pref_B[i] = pref_B[i - 1] + energyDrinkB[i - 1];
        }
        for (int i = n - 2; i >= 0; i--)
        {
            suff_A[i] = suff_A[i + 1] + energyDrinkA[i + 1];
            suff_B[i] = suff_B[i + 1] + energyDrinkB[i + 1];
        }
        long long maxi = 0;
        for (int i = 0; i < n; i++)
        {
            long long c = max({
                pref_A[i] + suff_A[i] + energyDrinkA[i],
                pref_B[i] + suff_B[i] + energyDrinkB[i],
                pref_A[i] + suff_B[i],
                pref_B[i] + suff_A[i],
            });
            maxi = max(maxi, c);
        }
        return maxi;
    }
};