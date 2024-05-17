#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(k);
    set<int> stb;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++)
    {
        cin >> b[i];
        stb.insert(b[i]);
    }
    // check if b has more than one disntinct element
    if (stb.size() > 2)
    {
        cout << "YES\n";
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == 0)
            {
                a[i] = b[0];
            }
        }
        // check if a is non-decreasing
        bool result = false;
        for (int i = 1; i < n; i++)
        {
            if (a[i] <= a[i - 1])
            {
                result = true;
            }
        }
        cout << (result ? "YES" : "NO") << endl;
    }
}