#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> sieveOfErasthonese(int maxi)
    {
        vector<int> ans;
        vector<bool> isPrimes(maxi + 1, true);
        for (int i = 2; i * i <= maxi; i++)
        {
            if (isPrimes[i] == true)
            {
                ans.push_back(i);
                for (int j = i * i; j < maxi; j += i)
                {
                    isPrimes[j] = false;
                }
            }
        }
        return ans;
    }
    map<int, int> divisors(vector<int> primes, int n)
    {
        map<int, int> ans;
        for (int i : primes)
        {
            if (i * i > n)
            {
                // not a factor
                break;
            }
            while (n >= i * i && n % i == 0)
            {
                ans[i]++;
                n = n / i;
            }
        }
        if (n > 1)
        {
            ans[n]++;
        }
        return ans;
    }
    int sumOfDivisors(const map<int, int> &factors)
    {
        int sum = 1;
        for (const auto &[p, exp] : factors)
        {
            // Integer arithmetic to avoid precision issues with pow
            int term = 1;
            int p_pow = 1;
            for (int i = 0; i <= exp; ++i)
            {
                term += p_pow;
                p_pow *= p;
            }
            sum *= term;
        }
        return sum;
    }
    int sumFourDivisors(vector<int> &nums)
    {
        int maxi = *max_element(nums.begin(), nums.end());
        vector<int> primes = sieveOfErasthonese(maxi);
        int sum = 0;
        for (int n : nums)
        {
            map<int, int> ans = divisors(primes, n);
            // getting the divisor count
            int divisorCount = 1;
            for (auto [p, exp] : ans)
            {
                divisorCount *= (exp + 1);
            }
            if (divisorCount == 4)
            {
                sum += sumOfDivisors(ans);
            }
        }
        return sum;
    }
};