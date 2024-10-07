#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int mergeStones(vector<int> &stones, int k) {
    int cost = 0;
    while (stones.size() >= k and stones.size()>1) {
      int n = stones.size();
      int windowSum = 0, miniSum = INT_MAX;
      int end = k - 1;
      for (int i = 0; i < k; i++) {
        windowSum += stones[i];
      }
      if (miniSum > windowSum) {
        miniSum = windowSum;
      }
      for (int i = k; i < n; i++) {
        windowSum += stones[i] - stones[i - k];
        if (miniSum > windowSum) {
          miniSum = windowSum;
          end = i;
        }
      }
      cout << "final array sum = " << miniSum << endl;
      for (int i = end - k + 1; i <= end; i++) {
        cout << stones[i] << " ";
      }
      cout << endl;
      cost += miniSum;
      vector<int> temp;
      for (int i = 0; i < end - k+1; i++) {
        temp.push_back(stones[i]);
      }
      temp.push_back(miniSum);
      for (int i = end + 1; i < n; i++) {
        temp.push_back(stones[i]);
      }
      cout<<"Temp array:-";
      for (int i : temp) {
        cout<<i<<" ";
      }
      cout<<endl;
      stones = temp;

    }
    if(stones.size()!=1){
      cost = -1;
    }
    cout<<"Cost = "<<cost<<endl;
    return cost;
  }
};
int main (int argc, char *argv[]) {
  vector<int> stones = {3,2,4,1};
  int k = 2;
  Solution().mergeStones(stones, k);
  return 0;
}
