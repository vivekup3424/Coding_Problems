// There are n apples with known weights.
// Your task is to divide the apples into
// two groups so that the difference between
// the weights of the groups is minimal.
//
// Input
//
// The first input line has an integer n:
// the number of apples.
//
// The next line has n integers p1,p2,…,pn:
// the weight of each apple.
//
// Output
//
// Print one integer: the minimum difference
// between the weights of the groups.

// This question I have done before, this question
// is like a min differnce subset sum problem of DP
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
bool is_subset_sum(vector<llu> v, int n, llu subset_sum) // n = no of elements from {1,2,3...n-1}
{
    bool t[n + 1][subset_sum + 1];
    memset(t, 0, (n + 1) * (subset_sum + 1));
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < subset_sum + 1; j++)
        {
            if (j == 0)
                t[i][j] = true;
            else if (i == 0)
                t[i][j] = false;
            else if (v[i - 1] > subset_sum) // don't include it
            {
                t[i][j] = t[i - 1][j];
            }
            else if (v[i - 1] <= subset_sum) // we now have a choice of whether to include the nth element in the subset or not
            {
                t[i][j] = t[i - 1][j - v[i - 1]] || t[i - 1][j]; // include or don't include
            }
        }
    }
    return t[n][subset_sum];
}
int minimum_difference(vector<llu> v)
{
    llu sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }
    llu subset_sum = 0;
    for (int i = sum / 2; i >= 0; i++)
    {
        if (is_subset_sum(v, v.size(), i))
        {
            subset_sum = i;
            break;
        }
    }
    return (sum - (2 * subset_sum));
}
int main()
{
    fast_io();
    // int T;
    // cin >> T;
    // while (T--)
    int n;
    cin >> n;
    vector<llu> apples(n);
    for (int i = 0; i < n; i++)
    {
        cin >> apples[i];
    }
    cout << minimum_difference(apples);
}
