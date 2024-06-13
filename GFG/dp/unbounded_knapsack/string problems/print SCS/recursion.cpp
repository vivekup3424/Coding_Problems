// Given two strings X and Y,
// print the shortest string that has both X and Y as subsequences.
// If multiple shortest supersequence exists, print any one of them.
//
// Examples:
//
// Input: X = "AGGTAB",  Y = "GXTXAYB"
// Output: "AGXGTXAYB" OR "AGGXTXAYB"
// OR Any string that represents shortest
// supersequence of X and Y
//
// Input: X = "HELLO",  Y = "GEEK"
// Output: "GEHEKLLO" OR "GHEEKLLO"
// OR Any string that represents shortest
// supersequence of X and Y
#include <bits/stdc++.h>
using namespace std;
int LCS(string x, string y, int a, int b) // a = x.size()
{
    if (a == 0 or b == 0)
        return 0; // base case
    else if (x[a - 1] == y[b - 1])
        return 1 + LCS(x, y, a - 1, b - 1);
    else
        return max(LCS(x, y, a, b - 1), LCS(x, y, a - 1, b));
}
// prints the shortest common subsequence for a pair of strings
void printSCS(string x, string y, int a, int b)
{
}
int main(){};
