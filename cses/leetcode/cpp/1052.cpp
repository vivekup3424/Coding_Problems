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

class Solution
{
public:
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int m)
    {
        // calculate the initial result, with no alterations
        ll happy = 0;
        ll n = customers.size();
        for (int i = 0; i < n; i++)
        {
            if (grumpy[i] == 0)
            {
                happy += customers[i];
            }
        }
        // get the initial window
        int left = 0, right = 0;
        ll maxSum = 0, currenSum = 0;
        for (; right < 3; right++)
        {
            if (grumpy[right] == 1)
            {
                currenSum += customers[right];
                maxSum = max(maxSum, currenSum);
            }
        }
        for (; right < n;)
        {
            if (grumpy[left] == 1)
            {
                currenSum -= customers[left];
            }
            if (grumpy[right] == 1)
            {
                currenSum += customers[right];
            }
            maxSum = max(maxSum, currenSum);
            left++;
            right++;
        }
        return maxSum + happy;
    }
};

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vi customers(n);
        inputVector(customers, n);
        vi grumpy(n);
        inputVector(grumpy, n);
        int minutes;
        cin >> minutes;
        cout << Solution().maxSatisfied(customers, grumpy, minutes) << endl;
    }
}