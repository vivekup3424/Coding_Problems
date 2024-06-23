#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;

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
//how to prove the below method mathematically
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,p;
        cin>>n>>p;
        vll a(n);
        inputVector(a,n); //max-shares
        vll b(n);
        inputVector(b,n); //share-cost
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, 
        greater<pair<ll,ll>>> minHeap;
        for (int i = 0; i < n; i++)
        {
            minHeap.push({b[i], a[i]});
        }
        ll total_cost = 0;
        ll total_spread = 0;
        while (total_spread<n)
        {
            if(minHeap.empty()==false and minHeap.top().first <= p){
                total_cost+=p;
                total_spread++;
                int spread = min(n-total_spread, minHeap.top().second);
                total_spread += spread;
                total_cost += spread*minHeap.top().first;
                minHeap.pop();
            }
            else{
                int spread = n - total_spread;
                total_cost += spread*p;
            }
        }
        cout<<total_cost<<endl;
    }
}