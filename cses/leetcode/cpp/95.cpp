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
    void generateAllTrees(vector<TreeNode *> &ans, int start, int end)
    {
        if (start > end)
        {
            ans.push_back(NULL);
            return;
        }
        for (int i = start; i <= end; i++)
        {
            vector<TreeNode *> left;
            vector<TreeNode *> right;
            generateAllTrees(left, start, i - 1);
            generateAllTrees(right, i + 1, end);
            for (int j = 0; j < left.size(); j++)
            {
                for (int k = 0; k < right.size(); k++)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = left[j];
                    root->right = right[k];
                    ans.push_back(root);
                }
            }
        }
    }
    vector<TreeNode *> generateTrees(int n)
    {
        vector<TreeNode *> ans;
        if (n == 0)
            return ans;
        generateAllTrees(ans, 1, n);
        return ans;
    }
};
int main()
{
}