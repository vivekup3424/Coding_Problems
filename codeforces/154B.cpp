#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 1;
int main()
{
    // get the list of all divisors of numbers till MAX in O(nlogn) time
    // using harmonic series and sieve
    vector<bool> isPrime(MAX, true);
    vector<vector<int>> divisors(MAX);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; i++)
    {
        if (isPrime[i] = true)
        {
            for (int j = i + i; j < MAX; j++)
            {
                isPrime[j] = false;
                divisors[j].push_back(i);
            }
        }
    }

    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> state(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        char sign;
        int num;
        scanf("%c %d", &sign, &num);
        if (sign == '+')
        {
            for (int i : divisors[num])
            {
                if (state[i] > 0)
                {
                    printf("Conflict with %d\n", i);
                    break;
                }
            }
        }
    }
}