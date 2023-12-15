
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxKDivisibleComponents(int n, vector<vector<int>> &edges, vector<int> &values, int k)
    {
        vector<long long> dp(n, 0);
        vector<vector<int>> tree(n);
        for (auto edge : edges)
        {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        int ans = 0;
    }
};
int main()
{
    int n = 9;
    vector<vector<int>> edges = {{0, 2},
                                 {1, 2},
                                 {1, 3},
                                 {2, 4}};
    vector<int> values = {1, 8, 1, 4, 4};
    int k = 6;
    Solution A = Solution();
    int m = A.maxKDivisibleComponents(n, edges, values, k);
}