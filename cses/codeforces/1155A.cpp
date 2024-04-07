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
    T = 1;
    while (T--)
    {
        ll n;
        cin>>n;
        string s;
        cin>>s;
        bool isDecreasing = false;
        pair<int,int> p =  {-1,-1};
        for(int i = 1; i < n; i++){
            if(s[i]<s[i-1]){
                isDecreasing = true;
                p = {i-1,i};
                break;
            }
        }
        if(isDecreasing){
            cout<<"YES"<<endl;
            cout<<p.first+1<<" "<<p.second+1<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
}
