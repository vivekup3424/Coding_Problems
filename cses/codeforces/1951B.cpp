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
        k--;
        vll v(n,0);
        inputVector(v,n); 
        //if lossing in the first step, we have two choices
        //replace with the first element or the second element, naturally it is to be replaced with the first largest element
        //so I will do 2 iterations
        ll count1 = 0;
        ll count2 = INT_MIN;
        for(int i = 0; i < n; i++){
            if(i!=k){
                if(v[i]<=v[k])count1++;
                else break;
            }
        }
        if(v[0]>v[k]){
                for(int i = 0; i < n; i++){
            if(i!=k and v[i]>v[k]){
                swap(v[i],v[k]);
                k = i;
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if(i!=k){
                if(v[i]<=v[k])count2++;
                else break;
            }
        }for(int i = 0; i < n; i++){
            if(i!=k and v[i]>v[k]){
                swap(v[i],v[k]);
                k = i;
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if(i!=k){
                if(v[i]<=v[k])count2++;
                else break;
            }
        }

        } 
        cout<<max(count1,count2)<<endl;
    }
}