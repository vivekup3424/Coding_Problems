#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    ll n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    // max_diff = 5
    int max_length = 1;
    int l = 0, r = 0;
    sort(v.begin(), v.end());
    while (r < n and v[r] - v[l] <= 5)
    {
        r++;
        while (l <= r and abs(v[r] - v[l]) > 5)
        {
            l++;
        }
        if (r < n)
        {
            max_length = max(max_length, r - l + 1);
        }
    }
    std::cout << max_length << endl;
    return 0;
}
