#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == b)
        {
            cout << (c % 2 == 1 ? "First" : "Second") <<endl;
        }
        else{
            cout<< (a > b ? "First" : "Second") <<endl;
        }
    }
}