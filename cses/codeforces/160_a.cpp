
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        sum += v[i];
    }
    sort(v.rbegin(), v.rend());
    int s = 0, c = 0;
    for (int n : v)
    {
        s += n;
        c++;
        if (s > sum - s)
        {
            cout << c << endl;
            break;
        }
    }
    return 0;
}