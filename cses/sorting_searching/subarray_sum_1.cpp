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
// Function to count the number of subarray with sum = X
ll solve(ll N, ll X, vector<ll> &arr)
{
    // Two pointers to mark the starting and ending of
    // sliding window
    ll start = 0, end = -1;
    // Variable to store sum of all elements in the current
    // sliding window
    ll sum = 0;
    // Variable to store the count of subarrays with sum = X
    ll cnt = 0;

    while (end < N)
    {
        // Increase the size of sliding window by moving the
        // end till the sum is smaller than X
        while (end < N && sum < X)
        {
            end += 1;
            sum += arr[end];
        }
        // Decrease the size of sliding window by moving the
        // start till the sum is greater than X
        while (start <= end && sum > X)
        {
            sum -= arr[start];
            start += 1;
        }

        // If the sum is equal to X, increase the count by 1
        if (sum == X)
        {
            cnt += 1;
            sum -= arr[start];
            start += 1;
        }
    }
    return cnt;
}
int main()
{
    fast_io();
    ll n, x;
    cin >> n >> x;
    vll a(n);
    inputVector(a, n);
    cout << solve(n, x, a) << endl;
}
