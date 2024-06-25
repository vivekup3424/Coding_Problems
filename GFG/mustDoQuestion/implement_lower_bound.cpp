// find the first value that is greater than or equal to x
// return index
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int lowerBound(vector<int> v, int x)
{
    int val = -1;
    int n = v.size();
    int l = 0, r = n;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (v[mid] >= x)
        {
            r = mid - 1;
            val = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << "index = " << val << endl;
    return val;
}
int main(int argc, char const *argv[])
{
    ll n, x;
    cin >> n >> x;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    lowerBound(v, x);
    return 0;
}
