#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e8;
bool prime[MAX + 1]; // for normal sieve

vector<int> normal_seive()
{
    // O(nloglogn) time complexity
    memset(prime, true, MAX + 1); // mark all of them initially as true
    for (ll i = 2; i <= MAX; i++)
    {
        if (prime[i])
        {
            for (ll j = i * i; j <= MAX; j += i)
            {
                prime[j] = false;
            }
        }
    }
}

int main()
{
    normal_seive();

    for (int)
}