#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    ll count = 1;
    while (n--)
    {
        count = count << 1;
        count %= MOD;
    }
    cout << count << endl;
    return 0;
}
