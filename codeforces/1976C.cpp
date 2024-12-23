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

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n, m;
        cin >> n >> m;
        vll prog(n + m + 1);
        inputVector(prog, n + m + 1);
        vll tester(n + m + 1);
        inputVector(tester, n + m + 1);
        vll answer(n + m + 1);
        for (int i = 0; i < n + m + 1; i++)
        {
            int programmers = n;
            int testers = m;
            int sum = 0;
            for (int j = 0; j < n + m + 1; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else if (prog[j] > tester[j])
                {
                    if (programmers > 0)
                    {
                        sum += prog[j];
                        programmers--;
                    }
                    else
                    {
                        sum += tester[j];
                        testers--;
                    }
                }
                else
                {
                    if (testers > 0)
                    {
                        sum += tester[j];
                        testers--;
                    }
                    else
                    {
                        sum += prog[j];
                        programmers--;
                    }
                }
            }
            answer[i] = sum;
        }
        outputVector(answer, answer.size());
    }
}