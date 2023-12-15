// given an edge list of an undirected graph with N nodes, and M edges,
// print an euler pathas edges sequence if no such euler path exists print -1

/**
 * Euler path visites every edge exactly once
 * 1. The graph should be connected, so that every edge can be pass thru from a particular node (starting node)
 * 2. for undirected , the number of nodes with odd degree can be atmost 2, and other nodes should have odd degree
 */
#include <bits/stdc++.h>
using namespace std;
vector<int> printEulerPath(int n, vector<vector<int>> &edgeList)
{
    // Prerequisites:-
    // 1. Since the graph should be a connected graph but if I am about to check this then that would result in increase time complexity
    // 2. Hence I would  only check the second condition, if the #nodes with odd degree is atmost 2
}