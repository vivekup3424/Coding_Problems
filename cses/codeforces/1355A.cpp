#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
pair<lli, lli> minMax(lli n) {
    lli min_element = LLONG_MAX;
    lli max_element = LLONG_MIN;

    while (n > 0) {
        lli t = n % 10;
        min_element = min(min_element, t);
        max_element = max(t, max_element);
        n /= 10;
    }

    return {min_element, max_element};
}

int main() {
    fast_io();
    lli T;
    cin >> T;

    while (T--) {
        lli n, k;
        cin >> n >> k;

        for (lli i = 1; i < k; i++) {
            pair<lli, lli> p = minMax(n);
            lli a = p.first;
            lli b = p.second;

            if (a == 0) break;
            else n = n + (a * b);
        }

        cout << n << endl;
    }

    return 0;
}