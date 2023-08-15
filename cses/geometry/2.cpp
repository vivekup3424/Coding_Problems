// given n integers, you task is to report for each intreger the number of its divisors
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
vector<ll> primes;
vector<ll> sieve;
void Sieve(ll n)
{
    int sieve_size = n;
    ll count = 0;
    sieve[0] = sieve[1] = 1;
    sieve[2] = 0;
    for (int x = 2; x <= n; x++)
    {
        if (!sieve[x]) // if its zero, then prime
        {
            primes.emplace_back(x);
            continue;
        }
        for (int u = 2 * x; u <= n; u += x)
        {
            sieve[u] = 0;
        }
    }
}
ll CountDivisors(ll x)
{
    ll i = 0, PF = primes[i], ans = 1;
    while (PF * PF <= x)
    {
        ll power = 0;
        while (x % PF == 0)
        {
            x /= PF;
            power++;
        }
        ans *= power + 1;
        PF = primes[i++];
    }
    if (x != 1)
        ans *= 2; // Last factor has pow=1,we add 1 to it
    return ans;
}
int main()
{
    ll n;
    cin >> n;
    while (n--)
    {
        ll x;
        cin >> x;
        Sieve(x);
        cout << CountDivisors(x) << "\n";
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
ll sieve_size;
bitset<10000010> bs;
vector<ll> primes;
void Sieve(ll x)
{
    sieve_size = x;
    ll count = 0;
    bs.set();
    bs[0] = bs[1] = false;
    for (ll i = 2; i <= sieve_size; i++)
    {
        if (bs[i])
        {
            for (ll j = i * i; j <= sieve_size; j += i)
            {
                bs[j] = false;
            }
            primes.emplace_back(i);
            count++;
        }
    }
}
ll CountDivisors(ll x)
{
    ll i = 0, PF = primes[i], ans = 1;
    while (PF * PF <= x)
    {
        ll power = 0;
        while (x % PF == 0)
        {
            x /= PF;
            power++;
        }
        ans *= power + 1;
        PF = primes[i++];
    }
    if (x != 1)
        ans *= 2; // Last factor has pow=1,we add 1 to it
    return ans;
}
int main()
{
    ll n;
    cin >> n;
    while (n--)
    {
        ll x;
        cin >> x;
        Sieve(x);
        cout << CountDivisors(x) << "\n";
    }
    return 0;
}
