#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> v(k);
        for (int &i : v)
        {
            cin >> i;
        }
        sort(v.begin(), v.end());
        int sum = 0;
        for (int i = 0; i < k - 1; i++)
        {
            sum += 2 * v[i] - 1;
        }
        cout << sum << endl;
    }
    return 0;
}
