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
        ll n;
        cin>>n;
        vll v(n,0);
        inputVector(v,n);
        //check if all elements are equal, because that;s 
        //the only way we would get -1 as ans
        set<int> st;
        for (int i = 0; i < n; i++)
        {
            st.insert(v[i]);
        }
        //cout<<"Printing the set\n";
        //for(auto it:st){
        //    cout<<it<<" ";
        //}
       // cout<<endl;
        bool all_equal = false;
        if(st.size()==1){
            all_equal==true;
        }
        int first = 0, last = 0;
        for(int i = 0; i < n; i++){
            if(v[i]==v.back())first++;
            else break;
        }   
        for(int i = n-1; i >=0; i--){
            if(v[i]==v.front())last++;
        }   
        if(all_equal){
            cout<<-1<<endl;
        }
        else{
            cout<<min(first,last)<<endl;
        }
    }
}