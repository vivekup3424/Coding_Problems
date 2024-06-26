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
// Make the check function to check if we can make T
// products in time <= mid
bool check(ll mid, ll N, ll T, ll *K)
{
    // Variable to count the number of products made
    ll sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += (mid / K[i]);
        if (sum >= T)
            return true;
    }
    return false;
}

// Function to find the minimum time to make T products
ll solve(ll N, ll T, ll *K)
{
    // Define the range in which our answer can lie
    ll low = 1, high = (*max_element(K, K + N)) * T;
    ll ans;

    // Binary Search for the minimum time to make T products
    while (low <= high)
    {
        ll mid = (low + high) / 2;

        // Check if we can make T products in time <= mid
        if (check(mid, N, T, K))
        {
            // Update the answer and reduce search space by
            // moving high to mid - 1
            ans = mid;
            high = mid - 1;
        }
        else
        {
            // Reduce the search space by moving low to mid
            // + 1
            low = mid + 1;
        }
    }
    return ans;
}
int main()
{
    ll n, t;
    cin >> n >> t;
    ll k[n];
    for (int i = 0; i < n; i++)
    {
        cin >> k[i];
    }
    cout << solve(n, t, k) << endl;
}