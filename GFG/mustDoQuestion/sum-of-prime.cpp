#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/**
 Given a number n, find out if n can be expressed as a+b, where both a and b are prime numbers. If such a pair exists, return the values of a and b, otherwise return [-1,-1] as an array of size 2.
Note: If [a, b] is one solution with a <= b, and [c, d] is another solution with c <= d, and a < c then  [a, b] is considered as our answer.*
*/
bool SieveOfEratosthenes(int n, bool isPrime[])
{
    // Initialize all entries of boolean array as true. A
    // value in isPrime[i] will finally be false if i is Not
    // a prime, else true bool isPrime[n+1];
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; i++)
        isPrime[i] = true;

    for (int p = 2; p * p <= n; p++)
    {
        // If isPrime[p] is not changed, then it is a prime
        if (isPrime[p] == true)
        {
            // Update all multiples of p
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }
}
vector<int> getPrimes(int n)
{
    // Generating primes using Sieve
    bool isPrime[n + 1];
    SieveOfEratosthenes(n, isPrime);

    // Traversing all numbers to find first pair
    for (int i = 0; i < n; i++)
    {
        if (isPrime[i] && isPrime[n - i])
        {
            return {i, n - i};
        }
    }
}
vector<int> getPrimes(int n)
{
    // get the list of all primes using sieve of erasthones
}