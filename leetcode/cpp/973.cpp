#include <bits/stdc++.h>
#include <queue>
using namespace std;

class Node {
public:
  int distanceSquared;
  int x;
  int y;
  Node(int d, int x, int y) {
    this->distanceSquared = d;
    this->x = x;
    this->y = y;
  }
};
class comparator {
public:
  bool operator()(Node* A, Node* B) {
    return A->distanceSquared < B->distanceSquared;
  }
};
class Solution {
public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    int n = points.size();
    priority_queue<Node*, vector<Node*>, comparator> maxHeap;
    for (int i = 0; i < n; i++) {
      int x = points[i][0], y = points[i][1];
      int d = x * x + y * y;
      auto A = new Node(d, x, y);
      maxHeap.push(A);
    }
    
    // Remove elements to maintain top k elements in maxHeap
    while (maxHeap.size() > k) {
      maxHeap.pop();
    }

    vector<vector<int>> v;
    while (maxHeap.size() > 0) {
      auto A = maxHeap.top();
      v.push_back({A->x, A->y});
      maxHeap.pop();
    }

    return v;
  }
};
