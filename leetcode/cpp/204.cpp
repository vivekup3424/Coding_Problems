#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countPrimes(int n)
    {
        vector<bool> isPrimes(n + 1, true);
        int count = 0;
        for (int i = 2; i < n; i++)
        {
            if (isPrimes[i])
            {
                count++;
                for (int j = i * i; j <= n; j += i)
                {
                    isPrimes[j] = false;
                }
            }
        }
        return count;
    }
};