#include <bits/stdc++.h>
#include <queue>
using namespace std;

class KthLargest {
private:
  priority_queue<int, vector<int>, greater<int>> minHeap;
  int heapSize;

public:
  KthLargest(int k, vector<int> &nums) {
        heapSize = k;
    for (auto i : nums) {
      minHeap.push(i);
      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
  }

  int add(int val) {
    minHeap.push(val);
    if (minHeap.size() > heapSize) {
      minHeap.pop();
    }
    return minHeap.top();
  }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
int main(){
    vector<int> v = {7,7,7,7,8,3};
    auto A = new KthLargest(4,v);
}
