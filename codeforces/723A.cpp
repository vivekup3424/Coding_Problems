#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int a, b, c;
    cin >> a >> b >> c;
    vector<int> v = {a, b, c};
    sort(v.begin(), v.end());
    cout << abs(v[1] - v[0]) + abs(v[2] - v[1]) << endl;
    return 0;
}
