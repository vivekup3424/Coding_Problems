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
llu amount(vector<int> a, vector<int> b, int x)
{
    // if x cookies are made, amound of magic powder required
    int n = a.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += max(0, a[i] * x - b[i]);
    }
    return sum;
}
int main()
{
    llu n, k;
    cin >> n >> k;
    vector<int> a(n, 0); // amount of ingredients requireed for each cookie
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    // ingredients already present
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    // now find the number of cookies using binary search
    llu low = 0, high = k + 1000, z = 0, ans = 0;
    while (low <= high)
    {
        llu mid = low + (high - low) / 2;
        z = amount(a, b, mid);
        if (z == k)
        {
            cout << mid << endl;
            return 0;
        }
        else if (z > k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
            ans = mid;
        }
    }
    cout << ans << endl;
    return 0;
}