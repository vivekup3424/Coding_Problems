// Increasing Array

// You are given an array of n integers.
// You want to modify the array so that it is increasing, i.e.,
// every element is at least as large as the previous element.
// On each move, you may increase the value of any element by one.
// What is the minimum number of moves required?

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
int positiveDiff(int a, int b) // a -b
{
    if (a - b < 0)
        return 0;
    return a - b;
}
int main()
{
    int n;
    cin >> n;
    vector<llu> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    llu result = 0;
    for (int i = 1; i < n; i++)
    {
        if (v[i] >= v[i - 1])
            continue;
        else if (v[i] < v[i - 1])
        {
            result += (v[i - 1] - v[i]);
            v[i] = v[i - 1];
        }
    }
    cout << result << "\n";
}
