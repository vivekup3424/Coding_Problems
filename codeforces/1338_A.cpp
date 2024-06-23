#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

vector<int> precalculatePowersOfTwo(int limit){
    vector<int> powersOfTwo(limit);
    int power = 1;
    for(int i = 0; i < limit; i++){
        powersOfTwo[i] = power;
        power *= 2;
    }
    return powersOfTwo;
}

int upperBound(vector<int>& powersOfTwo, int n){
    return lower_bound(powersOfTwo.begin(), powersOfTwo.end(), n) - powersOfTwo.begin();
}

int main()
{
    fast_io();
    int T;
    cin >> T;
    vector<int> powersOfTwo = precalculatePowersOfTwo(31); // Pre-calculate powers of 2
    while (T--)
    {
     int n;
     cin>>n;
     vector<int> v(n,0);
     for(int i = 0; i<n;i++)   
    {
        cin>>v[i];
    }
    int maxCount = 0;
    for(int i = 1; i < n; i++)
    {
        if(v[i]<v[i-1]){
            int diff = v[i-1] - v[i];
            int count = upperBound(powersOfTwo, diff);
            int val = powersOfTwo[count];
            v[i] += val;
            maxCount = max(maxCount, count+1);
        }
    }
    cout<< maxCount<<endl;
    }
}