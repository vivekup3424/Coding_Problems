#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int findMin(vector<int> v){
        int n = v.size();
        int l = 0, r = n-1, m = 0;
        int miniElement = v[0];
        while(l<=r){
            if (v[l] < v[r]) {
                miniElement = min(miniElement, v[l]);
                break;
            }
            m = (l+r)/2;
            miniElement = min(miniElement, v[m]);
            if(v[m] >=  v[l]){
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        return miniElement;
    }
};
int main()
{
    vector<int> v = {5,1,2,3,4};
    Solution A;
    cout<<A.findMin(v)<<endl;
}

