#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
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
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
void something(ll x, int idx, int prev_state, vector<int> &taken, vector<int> &finalAnswer)
{
    if (finalAnswer.size() != 0)
    {
        return;
    }
    if (x == 0)
    {
        finalAnswer = taken;
        return;
    }
    else if (idx >= 6)
    {
        return;
    }
    else
    {
        if (prev_state != 0)
        {
            taken.push_back(0); // since consecutive elements can't be
                                //  non-zero

            something(x, idx + 1, 0, taken, finalAnswer);
        }
        else
        {
            ll value = 1 << idx;
            // 1 at the idx
            taken.push_back(1);
            something(x - value, idx + 1, 1, taken, finalAnswer);
            taken.pop_back();
            //-1 at the idx
            taken.push_back(-1);
            something(x + value, idx + 1, -1, taken, finalAnswer);
            taken.pop_back();
            // not taking it, 0 at the idx
            taken.push_back(0);
            something(x, idx + 1, 0, taken, finalAnswer);
            taken.pop_back();
        }
    }
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        int x;
        cin >> x;
        vector<int> answer;
        vector<int> finalAnswer;
        something(x, 0, 0, answer, finalAnswer);
        cout << finalAnswer.size() << endl;
        for (auto i : finalAnswer)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}