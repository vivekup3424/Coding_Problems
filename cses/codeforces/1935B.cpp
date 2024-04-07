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
        vll v(n);
        inputVector(v,n);
        ll MEX = 0;
        for(ll r: v){
            if (MEX==r)
            {
                MEX++;
            }
        }
        vvll ans;
        //start forming the partitions
        int count = 0;
        ll start = 0, length = 0,last_mex = 0;
        while (start+length < n)
        {
            ll mex = 0;
            vll temp;
            while (mex<MEX and start+length<n)
            {
                if(mex==v[start+length])mex++;
                temp.push_back(v[start+length]);
                length++;
            }
            start = start+length+1;
            length = 0;
            count++;
            last_mex = mex;
            ans.push_back(temp);
        }
        if(last_mex==MEX){
            cout<<count<<endl;
            //print the matrix
            for(int i = 0; i <ans.size(); i++){
                outputVector(ans[i], ans[i].size());
            }
        }
        else{
            cout<<-1<<endl;
        }
    }
}
