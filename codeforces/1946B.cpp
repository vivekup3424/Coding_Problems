#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9+7;

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
ll maxSubArraySum(vll a, int n)
{
    ll max_so_far = 0, max_ending_here = 0,
        start = 0, end = 0, s = 0;
 
    for (ll i = 0; i < n; i++) {
        max_ending_here += a[i];
 
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
 
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    //cout << "Maximum contiguous sum is " << max_so_far
    //     << endl;
    //cout << "Starting index " << start << endl
    //     << "Ending index " << end << endl;
    return max_so_far;
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,k;
        cin>>n>>k;
        vll v(n);
        inputVector(v,n);
        ll sum = maxSubArraySum(v,n);
        ll total = 0;
        for(auto i: v){
            total += i;
        }
        // Calculate pow(2, k) % MOD
        ll pow2_k = 1;
        for (int i = 0; i < k; ++i) {
            pow2_k = (pow2_k * 2) % MOD;
        }
        
        // Calculate new_total without applying MOD
        ll new_total = ((pow2_k * sum) % MOD - sum + total)%MOD;
        
        // Adjust new_total to ensure it's non-negative and within MOD range
        new_total = (new_total % MOD + MOD) % MOD;
        
        cout<<new_total<<endl;
    }
}
