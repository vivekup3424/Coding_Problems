//Date 20-04-2024
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
int main()
{
    fast_io();
    llu n, m, k;
    cin >> n >> m >> k;
    vector<int> desired;
    vector<int> available;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        desired.push_back(temp);
    }
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        available.push_back(temp);
    }
    // k - max allowed difference
    sort(desired.begin(), desired.end());
    sort(available.begin(), available.end());
    vector<bool> taken(n,false);
    int count = 0;
    for(int i = 0; i < n; i++){
        int desired_size = desired[i];
        //do a binary search to find the lowest valid apartment-size
        //from the given values
        int l = 0, r = n-1;
        int mid = (l+r)/2;
        while(l<=r){
            if(available[i]-desired_size > k){
                r = mid-1; //go small
            }
            else if(abs(available[i]-desired_size) <= k){
                if(taken[i]==false){
                    taken[i] = true;
                    r = mid-1;
                    count++;
                }
                else{
                    l = mid+1;
                }
            }
            else if(available[i]-desired_size < -k){
                l = mid+1;
            }
        }
    }
    cout << count << "\n";
    return 0;
}