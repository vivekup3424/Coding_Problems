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

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,k;
        cin>>n>>k;
        ll max_two = 0;
        ll temp = k;
        while(temp>0){
            max_two++;
            temp>>=1;
        }
        vll ans;
        ll value = pow(2,max_two-1)-1;
        ll rest = k - value;
        if(n==1){
            cout<<k<<endl;
        }
        else if(n==2){
            cout<<value<<" "<<rest<<endl;
        }
        else{
            cout<<value<<" "<<rest<<" ";
            for(int i = 2; i < n; i++){
                cout<<0<<" ";
            }
            cout<<endl;
        }
    }
}