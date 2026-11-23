/*
 * 1877A. Goals of Victory
 * https://codeforces.com/problemset/problem/1877/A
 * Time limit: 1 second | Memory limit: 256 megabytes
 *
 * There are n teams in a football tournament. Each pair of teams match up
 * once. After every match, Team A scores some goals and Team B scores some
 * goals.
 *
 * The efficiency of a team is the total number of goals it scored in all its
 * matches minus the total number of goals it conceded in all its matches.
 * (The tournament has finished.)
 *
 * You are given the efficiency of the first n - 1 teams: a_1, a_2, ...,
 * a_{n-1}. Find the efficiency of the n-th team.
 *
 * It can be shown that the answer always exists and is unique.
 *
 * Input:
 *   Each test contains multiple test cases. The first line contains a
 *   single integer t (1 <= t <= 500) - the number of test cases.
 *
 *   The first line of each test case contains a single integer n
 *   (2 <= n <= 100) - the number of teams.
 *
 *   The second line of each test case contains n - 1 integers
 *   a_1, a_2, ..., a_{n-1} (-100 <= a_i <= 100) - the efficiency of the
 *   first n - 1 teams.
 *
 * Output:
 *   For each test case, output a single integer - the efficiency of the
 *   n-th team.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        int sum = 0;
        for(int i = 0; i < n-1; i++){
            int temp;
            cin>>temp;
            sum += temp;
        }
        cout << 0 - sum <<"\n";
    }
}
