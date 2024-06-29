#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    ll n;
    cin >> n;
    ll count = 0;
    while (n > 0)
    {
        count += n / 5;
        n = n / 5;
    }
    cout << count << endl;
    return 0;
}
