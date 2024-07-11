#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool isDistinct(int num)
{
    string numStr = to_string(num);
    set<char> s = set<char>(numStr.begin(), numStr.end());
    return s.size() == numStr.size();
}
int main(int argc, char const *argv[])
{
    int l, r;
    cin >> l >> r;
    if (l > r)
    {
        swap(l, r);
    }
    bool found = false;
    for (int i = l; i <= r; i++)
    {
        if (isDistinct(i))
        {
            cout << i << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << -1 << endl;
    }
    return 0;
}
