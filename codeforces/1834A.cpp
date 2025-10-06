#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        int countNeg = 0, countPos = 0;
        for (int i = 0; i < n; i++)
        {
            if(a[i]==-1)countNeg++;
            else countPos++;
        }
        int sum = accumulate(a.begin(), a.end(), 0);
        return countNeg % 2 == 1 ? cout << sum + 1 << endl : cout << sum << endl;
    }
}