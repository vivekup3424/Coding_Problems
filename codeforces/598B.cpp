#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    string str;
    cin >> str;
    ll q;
    cin >> q;
    while (q--)
    {
        ll l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        string temp = str;
        int n = r - l + 1;
        for (int i = 0; i < n; i++)
        {
            int new_position = (i + k) % n;
            temp[l + new_position] = str[i + l];
        }
        temp = str;
    }
    cout << str << endl;
    return 0;
}
