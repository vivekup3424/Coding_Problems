
#include <bits/stdc++.h>
using namespace std;
// A. Insert Digit
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, d;
        string num;
        cin >> n >> d;
        cin >> num;
        char c = d + '0';
        for (int i = 0; i < n; i++)
        {
            if (num[i] <= c)
            {
                num.insert(i, 1, c);
                break;
            }
        }
        cout << num << endl;
    }
}