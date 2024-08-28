#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int A, B, X;
        cin >> A >> B >> X;
        if (A * B <= X * X)
        {
            cout << 0 << endl;
        }
        else if (min(A, B) <= X * X)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}
