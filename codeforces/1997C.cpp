#include <bits/stdc++.h>
using namespace std;

// Type definitions
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
constexpr int MOD = 1e9 + 7;

// Fast I/O setup
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements into a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v)
{
    for (const auto item : v)
    {
        cout << item << " ";
    }
    cout << "\n";
}

// Calculate the cost of a balanced bracket sequence
int findCost(const string &s)
{
    stack<int> stk;
    int cost = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            stk.push(i);
        }
        else if (s[i] == ')')
        {
            if (!stk.empty())
            {
                cost += abs(i - stk.top()); // Corrected to use absolute difference
                stk.pop();
            }
            else
            {
                return INT_MAX;
            }
        }
    }
    if (stk.size() > 0)
    {
        return INT_MAX;
    }
    return cost;
}

// Recursively restore the bracket sequence and calculate the minimum cost
int recurse(vector<int> &memo, string s, int idx)
{
    if (memo[idx] != -1)
    {
        return memo[idx];
    }
    if (idx == 0)
    {
        int min_val = INT_MAX;
        if (s[idx] == '_')
        {
            s[idx] = '(';
            min_val = min(min_val, findCost(s));
            s[idx] = ')';
            min_val = min(min_val, findCost(s));
        }
        else
        {
            min_val = min(min_val, findCost(s));
        }
        return memo[idx] = min_val;
    }
    int min_val = INT_MAX;
    if (s[idx] == '_')
    {
        s[idx] = '(';
        min_val = min(min_val, recurse(memo, s, idx - 1));
        s[idx] = ')';
        min_val = min(min_val, recurse(memo, s, idx - 1));
    }
    else
    {
        min_val = min(min_val, recurse(memo, s, idx - 1));
    }
    return memo[idx] = min_val;
}

int main()
{
    freopen("/home/vivekup3424/Coding_Problems/input.txt", "r", stdin);
    // freopen("/home/vivekup3424/Coding_Problems/output.txt", "w", stdout);
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> memo(n, -1);
        cout << recurse(memo, s, n - 1);
    }

    return 0;
}
