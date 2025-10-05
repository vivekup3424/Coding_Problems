#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, x;
        cin >> n >> x;
        int prevNum = 0;
        int maxDiff = 0;

        for (int i = 0; i < n; i++)
        {
            int curr;
            cin >> curr;
            int diff = curr - prevNum;
            maxDiff = max(maxDiff, diff);
            prevNum = curr;
        }

        int diff = x - prevNum;
        diff *= 2;
        maxDiff = max(maxDiff, diff);

        cout << maxDiff << endl;
    }
}
