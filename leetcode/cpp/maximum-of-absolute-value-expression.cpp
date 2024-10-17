#include <bits/stdc++.h>
using namespace std;
void recurse(vector<vector<int>> &c, vector<int> v, int i, int n){
    if(i==n){
        c.push_back(v);
    }else{
        v.push_back(1);
        recurse(c,v,i+1,n);
        v.pop_back();
        v.push_back(-1);
        recurse(c,v,i+1,n);
        v.pop_back();
    }
}
vector<vector<int>> validCombinations(int n){
    vector<vector<int>> ans;
    vector<int> v;
    recurse(ans,v,0,n);
    return ans;
}
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        vector<vector<int>> ans = validCombinations(3);
        for(auto v : ans){
            for(auto i : v){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        return -1;
    }
};
int main(){
    vector<int> arr1 = {1,2,3,4};
    vector<int> arr2 = {-1,4,5,6};
    Solution().maxAbsValExpr(arr1,arr2);
    return 0;
}
