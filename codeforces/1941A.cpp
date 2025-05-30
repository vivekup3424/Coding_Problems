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

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,m,k;
        cin>>n>>m>>k;
        vll b(n,0);
        inputVector(b,n);
        vll c(m);
        inputVector(c,m);
        int count = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if((b[i]+c[j])<=k)count++;
            }
        }
        cout<<count<<endl;
    }
}
