#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long count_equal_substrings(const string &s)
{
    int n = s.length();
    map<int, int> prefix_count;
    prefix_count[0] = 1;
    long long prefix_diff = 0, result = 0;

    for (char ch : s)
    {
        // Update prefix_diff based on current character
        if (ch == '0')
        {
            prefix_diff++;
        }
        else
        {
            prefix_diff--;
        }

        // Count substrings with equal number of 0s and 1s
        if (prefix_count.find(prefix_diff) != prefix_count.end())
        {
            result += prefix_count[prefix_diff];
            result %= MOD;
        }

        // Update the count of the current prefix_diff
        prefix_count[prefix_diff]++;
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        string s;
        cin >> s;

        cout << count_equal_substrings(s) << endl;
    }

    return 0;
}
