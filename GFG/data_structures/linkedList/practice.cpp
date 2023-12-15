#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

using namespace std;

const int MOD = 1e9 + 7;

int count_permutations(vector<lli> &A)
{
    int n = A.size();
    int ans = 0;
    for (int m = 1; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            vector<int> subarray(A.begin() + i, A.begin() + i + m);
            set<int> distinct(subarray.begin(), subarray.end());
            if (distinct.size() == m && all_of(distinct.begin(), distinct.end(), [](int x)
                                               { return 1 <= x; x <= m; }))
            {
                ans = (ans + 1) % MOD;
            }
        }
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<lli> A(n);
        for (int i = 0; i < n; i++)
        {
            cin >> A[i];
        }
        int ans = count_permutations(A);
        cout << ans << endl;
    }
    return 0;
}
