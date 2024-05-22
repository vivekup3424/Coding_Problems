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
ll solve(vector<ll> &arr, ll N)
{
    // Sort the books in increasing order of their reading
    // times
    sort(arr.begin(), arr.end());

    // Store the largest reading time
    ll largest = arr[N - 1];

    // Store the sum of remaining remaining times
    ll sumOfSmaller = accumulate(arr.begin(), arr.end() - 1, 0LL);

    // If largest <= sumOfSmaller, then none of them will
    // have to wait and answer will be the sum of reading
    // times of all the books
    if (largest <= sumOfSmaller)
    {
        return sumOfSmaller + largest;
    }
    // Otherwise, one of them have to wait and the answer
    // will be 2 * largest reading time
    return 2 * largest;
}

int main()
{
    fast_io();
    ll T;
    T = 1;
    while (T--)
    {
        ll n;
        cin >> n;
        vll v(n);
        inputVector(v, n);
        ll maxi = solve(v, n);
        cout << maxi << endl;
    }
}