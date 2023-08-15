// Given a string, your task is to generate all different
// strings that can be created using its characters.
//
// Input
//
// The only input line has a string of length n.
// Each character is between a–z.
//
// Output
//
// First print an integer k: the number of strings.
// Then print k lines: the strings in alphabetical order.

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
int factorial(int n)
{
    int arr[n + 1];
    arr[0] = 1;
    for (int i = 1; i < n + 1; i++)
    {
        arr[i] = i * arr[i - 1];
    }
    return arr[n];
}
int main()
{
    fast_io();
    // int T;
    // cin >> T;
    // while (T--)
    {
        string str;
        cin >> str;
        map<char, int> freq;
        for (int i = 0; i < str.size(); i++)
        {
            freq[str[i]]++;
        }
        int deno = 1;
        for (auto i : freq)
        {
            deno *= factorial(i.second);
        }
        int product = factorial(str.size()) / deno;
        cout << product << "\n";
        sort(str.begin(), str.end()); // O(nlogn)
        do
        {
            cout << str << "\n";
        } while (next_permutation(str.begin(), str.end())); // O(n*n!)
    }
    return 0;
}