// You are given the arrival and leaving times of n customers in a restaurant.
//
// What was the maximum number of customers in the restaurant at any time?

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
    lli n;
    cin >> n;
    vector<lli> arrival;
    vector<lli> dept;
    lli maximum_entered = 0;
    for (int i = 0; i < n; i++)
    {
        lli a, b;
        cin >> a >> b;
        maximum_entered = max(maximum_entered, b);
        arrival.push_back(a);
        dept.push_back(b);
    }
    // can we use prefix sum here,??
    lli people[maximum_entered + 1];
    for (int i = 0; i < maximum_entered + 1; i++)
    {
        people[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        people[arrival[i]] = 1;
        people[dept[i]] = -1;
    }
    // now doing prefix sum
    for (int i = 1; i < maximum_entered + 1; i++)
    {
        people[i] = people[i] + people[i - 1];
    }
    lli most = 0;
    for (int i = 1; i < maximum_entered + 1; i++)
    {
        most = max(most, people[i]);
    }

    cout << most << "\n";
}