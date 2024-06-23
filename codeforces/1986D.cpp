#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to evaluate the arithmetic expression given the string and the operators
ll evaluateExpression(const string &s, const vector<char> &ops)
{
    vector<ll> terms;
    ll current_term = s[0] - '0';

    // First pass: handle multiplications
    for (int i = 0; i < ops.size(); i++)
    {
        if (ops[i] == '×')
        {
            current_term *= (s[i + 1] - '0');
        }
        else
        {
            terms.push_back(current_term);
            current_term = s[i + 1] - '0';
        }
    }
    terms.push_back(current_term);

    // Second pass: handle additions
    ll result = 0;
    for (ll term : terms)
    {
        result += term;
    }
    return result;
}

// Function to find the minimum result for a given string s
ll findMinimumResult(const string &s)
{
    int n = s.length();
    vector<char> ops(n - 1);
    ll min_result = LLONG_MAX;

    // Try all combinations of '+' and '×'
    for (int mask = 0; mask < (1 << (n - 1)); mask++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (mask & (1 << i))
            {
                ops[i] = '+';
            }
            else
            {
                ops[i] = '×';
            }
        }

        ll result = evaluateExpression(s, ops);
        min_result = min(min_result, result);
    }

    return min_result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        string s;
        cin >> n;
        cin >> s;

        ll result = findMinimumResult(s);
        cout << result << "\n";
    }

    return 0;
}
