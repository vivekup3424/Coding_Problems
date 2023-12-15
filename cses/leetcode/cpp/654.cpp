
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

class Solution
{
public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        sort(nums.rbegin(), nums.rend());
        queue<int> *q;
        for (int num : nums)
        {
            q->push(num);
        }
        TreeNode *root = new TreeNode(q->front());
        q->pop();
    }
};
int main()
{
}