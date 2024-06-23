
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int length = 1, max_length = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] <= v[i + 1])
        {
            length++;
        }
        else
        {
            length = 1;
        }
        max_length = max(max_length, length);
    }
    cout << max_length << endl;
}