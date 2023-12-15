// given a string and a pattern, your task is to count the number of positions
// where the pattern occurs in the string.

// Method 1: Polynomial Hashing
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 1;
const int A = 31;
const int B = 1e9 + 9;
typedef long long int lli;
lli h[N], p[N];
void precompute_hash(string s)
{
    h[0] = 0;
    p[0] = 1;                            // starting it from 1 index
    h[1] = s[0] - 'a' + 1;               // hash-code for each character
    p[1] = 1;                            // power of A
    for (auto i = 2; i <= s.size(); i++) // one indexed based array
    {
        h[i] = (h[i - 1] * A + (s[i - 1] - 'a' + 1)) % B;
        p[i] = (p[i - 1] * A) % B;
    }
    /*hash value of any
    substring s[a . . . b]
    (h[b] − h[a − 1]p[b − a + 1]) mod B*/
}
void printArray(lli a[], int size)
{
    for (auto i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << endl;
}
int get_hash(string p, int m)
{
    int hash_value = 0; // base-case
    for (auto s : p)
    {
        hash_value = (hash_value * A + (s - 'a' + 1)) % B;
    }
    return hash_value;
}
int main()
{
    string str, pattern;
    cin >> str >> pattern;
    int n = str.size(), m = pattern.size();
    // I think i am going to use polynomial hashing
    // first i will calculate the hash of the pattern
    // then I will calculate the prefix-hash of the string and store it in an array
    int hash_pattern = get_hash(pattern, m);
    precompute_hash(str);
    int counter = 0, hash_substring = 0;
    for (auto i = 1; i <= n - m; i++)
    {
        hash_substring = (h[i + m - 1] - h[i - 1] * pattern[m]) % B;
        if (hash_substring == hash_pattern)
            counter++;
    }
    printArray(h, n + 1);
    printArray(p, n + 1);
    cout << counter << endl;
    return 0;
}