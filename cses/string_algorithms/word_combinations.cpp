
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int MAXN = 5005;

/* You are given a string of length n and a dictionary containing
k words.
In how many ways can you create the string using the words?*/
int main()
{
    int n, k;
    string s;
    cin >> s;
    n = s.size();
    cin >> k;
    vector<string> dict(k);
    for (int i = 0; i < k; i++)
        cin >> dict[i];
    vector<int> dp(n + 1, 0); // initially all 0
    dp[0] = 1;                // empty string. 1 way to create it
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            string temp = s.substr(j, i - j + 1);
            if (find(dict.begin(), dict.end(), temp) != dict.end())
                dp[i + 1] = (dp[i + 1] + dp[j]) % mod;
        }
    }
    cout << dp[n] << endl;
    return 0;
}