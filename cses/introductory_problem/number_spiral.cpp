#include <iostream>
using namespace std;

typedef long long ll;

ll findNumberInSpiral(ll y, ll x)
{
    ll maxVal = max(y, x);
    ll cornerVal = maxVal * maxVal - maxVal + 1;

    if (maxVal % 2 == 0)
    {
        // Even maximum coordinate
        if (y == maxVal)
        {
            return cornerVal + (x - y);
        }
        else
        {
            return cornerVal - (y - x);
        }
    }
    else
    {
        // Odd maximum coordinate
        if (x == maxVal)
        {
            return cornerVal + (y - x);
        }
        else
        {
            return cornerVal - (x - y);
        }
    }
}

int main()
{
    ll t;
    cin >> t;

    while (t--)
    {
        ll y, x;
        cin >> y >> x;
        cout << findNumberInSpiral(y, x) << endl;
    }

    return 0;
}
