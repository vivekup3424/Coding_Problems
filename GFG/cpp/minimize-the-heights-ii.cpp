#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution{
    public:
    int getMinDiff(vector<int> arr, int k){
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int ans = arr[n-1] - arr[0];
        for(int i = 0; i < n-1; i++){
            if(arr[i+1] - k < 0) continue;
            int mini = min(arr[0]+k, arr[i+1]-k);
            int maxi = max(arr[i]+k, arr[n-1]-k);
            ans = min(ans, maxi - mini);
        }
        return ans;
    }
};