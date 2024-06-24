// this problem is very simila to 2-sum type of problemo
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    ll n, k;
    cin >> n >> k;
    vector<long long> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int count = 0;
    map<int, int> mp;
    for (int i : v)
    {
        ll element = i % k;
        ll complement = (k - element) % k;
        if (mp.find(complement) != mp.end())
        {
            count++;
            mp[complement]--;
            if (mp[complement] == 0)
            {
                mp.erase(complement);
            }
        }
        else
        {
            mp[element]++;
        }
    }
    cout << 2 * count << endl;
    return 0;
}
