
#include <bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// Method 1: Using Recursion and Memoization
const int N = 21;
int dp[N];
class Solution
{
public:
    // Generates the total number of possible full binary trees
    int allPossibleFBTs(int n)
    {
        for (int i = 0; i < N; i++)
        {
            // initialization
            if (i & 1 == 0)
            {
                dp[i] = 0;
            }
            else if (i == 1)
            {
                dp[i] = 1;
            }
            else
            {
                for (int j = 1; j < i - 1; j += 2)
                {
                    dp[i] += dp[j] * dp[i - j - 1]; // we are using the fact that the total number of possible full
                    // binary trees is the product of the total number of possible left and right subtrees
                }
            }
        }
        return dp[n];
    }
    vector<TreeNode *> allPossibleFBT(int n)
    {
        }
};
int main()
{
}