#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int recurse(int x, int y, int m)
{
    // assuming x is always less than y
    if (m < x)
    {
        return 0;
    }
    else if (m < y)
    {
        return m / x;
    }
    else
    {
        return max(1 + recurse(x, y, m - x), 1 + recurse(x, y, m - y));
    }
}
int main(int argc, char const *argv[])
{
    int x, y, m;
    cin >> x >> y >> m;
    if (x > y)
    {
        swap(x, y);
    }
    cout << recurse(x, y, m) << endl;
    return 0;
}
