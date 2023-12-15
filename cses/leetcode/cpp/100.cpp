
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        // recursive approach
        // base cases
        if (p == NULL && q == NULL)
            return true;
        else if ((p == NULL and q != NULL) or (p != NULL and q == NULL))
            return false;
        else if (p->val != q->val)
            return false;
        else
            return isSameTree(p->left, q->left) and isSameTree(p->right, q->right);
    }
};
int main()
{
}