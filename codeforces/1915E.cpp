#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
bool hasSubarray(const std::vector<long long>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        long long oddSum = 0;
        long long evenSum = 0;
        for(int j = i; j < n; j++){
            if (j % 2 == 0) {
                evenSum += arr[j];
            } else {
                oddSum += arr[j];
            }
            if(oddSum == evenSum)return true;
        }
    }

    return false; // No such subarray found
}
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        vector<long long> v(n);
        for(int i = 0; i <n;i++){
            cin>>v[i];
        }
        bool result = hasSubarray(v);
        if(result)cout<<"YES\n";
        else cout<<"NO\n";
        
    }
}