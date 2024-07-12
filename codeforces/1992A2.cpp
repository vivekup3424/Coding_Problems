#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        vector<int> v(3);
        for (int &i : v)
        {
            cin >> i;
        }
        for (int i = 0; i < 5; i++)
        {
            *min_element(v.begin(), v.end()) += 1;
        }
        cout << v[0] * v[1] * v[2] << endl;
    }
    return 0;
}