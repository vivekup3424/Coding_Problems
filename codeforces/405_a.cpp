#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[105];
int main()
{
    int n;
    while (cin >> n && n != EOF)
    {
        for (int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}
