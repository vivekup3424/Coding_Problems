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
    lli n, k;
    cin >> n >> k;

    vector<lli> lectures(n);
    vector<lli> sleep(n);
    for (lli i = 0; i < n; i++)
    {
        cin >> lectures[i];
    }
    for (lli i = 0; i < n; i++)
    {
        cin >> sleep[i];
    }

    vector<lli> p(n, 0);    // unaffected prefix of lectures, including the ith element
    vector<lli> pref(n, 0); // actual prefix of lectures
    vector<lli> suffix(n, 0);
    p[0] = lectures[0];
    for (lli i = 1; i < n; i++)
    {
        p[i] = p[i - 1] + lectures[i];
    }

    pref[0] = lectures[0] * sleep[0];

    for (lli i = 1; i < n; i++)
    {
        // inclusive prefix, including the ith element
        pref[i] = pref[i - 1] + (lectures[i] * sleep[i]);
    }

    // building the suffix array
    for (lli i = n - 2; i >= 0; i--)
    {
        // for suffix[i], not including the ith element
        suffix[i] = suffix[i + 1] + (lectures[i] * sleep[i]);
    }

    // now finding the maximum sum possible in linear time
    // think of the edge cases
    lli maxSum = INT_MIN;
    for (lli i = 0; i + k - 1 < n; i++)
    {
        lli sum = 0;
        if (i > 1)
        {
            sum += pref[i - 1];
        }
        if (i + k < n)
        {
            sum += suffix[i + k];
        }
        int range_sum = p[i + k - 1];
        if (i > 0)
        {
            range_sum -= p[i - 1]; // getting the range sum when Mishka is awake
        }
        sum += range_sum;
        if (sum > maxSum)
        {
            maxSum = sum;
        }
    }
    cout << maxSum << endl;
}