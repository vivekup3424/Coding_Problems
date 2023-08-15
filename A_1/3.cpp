// You are given a DNA sequence:
// a string consisting of characters A, C, G, and T.
// Your task is to find the longest repetition in the sequence.
// This is a maximum-length substring containing only one type of character.

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
// Kadane's algorithm
int maxLen(string str, lli length)
{
    fast_io();
    lli max_so_far = 1, current_max = 1, j = 0;
    while (j < length)
    {
        if (str[j] == str[j + 1])
            current_max++;
        else if (str[j] != str[j + 1])
        {
            current_max = 1;
        }
        if (current_max > max_so_far)
            max_so_far = current_max;
        j++;
    }
    cout << max_so_far << "\n";
    return max_so_far;
}
int main()
{
    string str;
    cin >> str;
    int length = str.size();
    maxLen(str, length);
    return 0;
}

// Homework
// https://cses.fi/problemset/
// first 15 problems