// Palindrome Reorder

// Given a string, your task is to reorder its letters in
// such a way that it becomes a palindrome(i.e., it reads
// the same forwards and backwards).

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
    string str;
    cin >> str;
    map<char, int> freq;
    stack<char> s;
    int odd_counter = 0;
    int length;
    for (int i = 0; i < str.size(); i++) // O(n)
    {
        freq[str[i]]++;
    }
    int odd_counter = 0;
    for (auto i : freq)
    {
        if (i.second % 2 == 1)
        {
            odd_counter++;
        }
        int even_freq = i.second / 2;
    }
}