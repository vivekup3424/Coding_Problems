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
int main()
{
    fast_io();
    int n, k;
    cin >> n >> k;
    vector<lli> start;
    vector<lli> finish;
    lli maximum_input = 0;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        maximum_input = max(a, b);
        start.push_back(a);
        finish.push_back(b);
    }
    int pfx[maximum_input + 1];
    for (int i = 0; i <= maximum_input; i++)
    {
        pfx[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        pfx[start[i]] = 1;
        pfx[finish[i]] = i;
    }
    int max_movies = 0;
    for (int i = 1; i <= maximum_input; i++)
    {
        pfx[i] = pfx[i] + pfx[i - 1];
        max_movies = max(max_movies, pfx[i]);
    }
    int result = min(max_movies, k);
    cout << result << "\n";
    return 0;
}