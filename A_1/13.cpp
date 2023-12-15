// A Gray code is a list of all 2n bit strings of length n,
// where any two successive strings differ in exactly
// one bit (i.e., their Hamming distance is one).
//
// Your task is to create a Gray code for a given length n.
//
// Input
//
// The only input line has an integer n.
//
// Output
//
// Print 2n lines that describe the Gray code.
// You can print any valid solution.
//
// Constraints
//
//     1≤n≤16

// 2^16=> usigned long long int

// I can use recursion for this question, as the
// time complexity is exponential for a minimum thing

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
    int T;
    cin >> T;
}