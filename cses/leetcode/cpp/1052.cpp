#include <iostream>
#include <vector>
#include <algorithm>
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
void outputVector(const vector<T> &v)
{
    for (const auto &el : v)
    {
        cout << el << " ";
    }
    cout << "\n";
}

class Solution
{
public:
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int m)
    {
        // Calculate the initial satisfied customers without alterations
        ll happy = 0;
        ll n = customers.size();
        for (int i = 0; i < n; i++)
        {
            if (grumpy[i] == 0)
            {
                happy += customers[i];
            }
        }

        // Sliding window to calculate the maximum additional satisfied customers
        ll maxSum = 0, currentSum = 0;
        for (int i = 0; i < m; i++)
        {
            if (grumpy[i] == 1)
            {
                currentSum += customers[i];
            }
        }
        maxSum = currentSum;

        for (int i = m; i < n; i++)
        {
            if (grumpy[i - m] == 1)
            {
                currentSum -= customers[i - m];
            }
            if (grumpy[i] == 1)
            {
                currentSum += customers[i];
            }
            maxSum = max(maxSum, currentSum);
        }

        return maxSum + happy;
    }
};

int main()
{
    fast_io();
    int n, m;
    cin >> n >> m;
    vi customers(n), grumpy(n);
    inputVector(customers, n);
    inputVector(grumpy, n);

    Solution sol;
    cout << sol.maxSatisfied(customers, grumpy, m) << "\n";

    return 0;
}
