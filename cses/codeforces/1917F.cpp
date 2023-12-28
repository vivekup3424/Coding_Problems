#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void generateSums1(int i, vector<int> arr, unordered_set<int> &ans, int *sum) {
    if (i == arr.size()) {
        ans.insert(*sum);
        return;
    }
    
    *sum += arr[i]; // including the ith element
    generateSums1(i + 1, arr, ans, sum);
    *sum -= arr[i]; // not including the ith element
    generateSums1(i + 1, arr, ans, sum);
}/*Some observations:-
1.If there exists two edges with sum > targer, then diameter is not possible.
 */
//now converting the above code to a bottom-up DP fashion
void generateSums2(vector<int> arr){
    int n  = arr.size();
    int t = accumulate(arr.begin(), arr.end(),0); //some value, here for exmaple target = total sum
    vector<vector<int>> dp(n+1, vector<int>(t+1,0));
    for(int i = 0; i <=n;i++){
        for(int j = 0;j<=t;j++){
            if(j==0)dp[i][j] = 1;
            else dp[i][j] = dp[i-1][j] | dp[i-1][j - arr[i-1]];
        }
    }
}
int main() {
    fast_io();
    vector<int> arr = {2,4,3,7,6,7};
    unordered_set<int> ans;
    int *sum = new int(0);
    generateSums1(0, arr, ans, sum);
    delete sum; // Don't forget to free the allocated memory
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
