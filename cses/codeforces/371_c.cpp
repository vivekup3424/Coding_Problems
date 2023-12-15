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
int pc, pb, ps;
int nb, ns, nc;
int cb, cs, cc;
// # bread = cb in the recipe and so on and so forth
llu fb, fc, fs;
llu price(llu x)
{
    fb = max((llu)0, x * cb - nb);
    fc = max((llu)0, x * cc - nc);
    fs = max((llu)0, x * cs - ns);
    return fb + fc + fs;
}
int main()
{
    string recipe;
    cin >> recipe;
    int n = recipe.length();
    cb = cc = cs = 0;
    for (char c : recipe)
    {
        switch (c)
        {
        case 'B':
            cb++;
            break;
        case 'S':
            cs++;
            break;
        case 'C':
            cc++;
            break;
        default:
            break;
        }
    }

    cin >> nb >> ns >> nc;
    cin >> pb >> ps >> pc;
    int r; // total monay
    cin >> r;
    llu low = 0, high = r + 1000, mid = 0, z = 0, ans = 0;
    while (low < high)
    {
        mid = (low + high) / 2;
        z = price(mid);
        if (z == r)
        {
            cout << mid << endl;
            return 0;
        }
        else if (z > r)
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
    // now calculation of x using binary search
}