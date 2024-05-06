#include <iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int S = 1000;
        cout << S << " ";
        for (int i = 2; i <= n; i++)
        {
            int x;
            cin >> x;
            S += x;
            cout << S << " ";
        }
        cout << "\n";
    }
}