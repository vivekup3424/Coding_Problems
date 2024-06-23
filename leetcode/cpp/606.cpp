
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
    void preOrder(TreeNode *root, string *data)
    {
        if (!root)
            return;
        data->push_back((char)(root->val + '0'));
        if (root->left == nullptr and root->right == nullptr)
            return;
        data->push_back('(');
        preOrder(root->left, data);
        data->push_back(')');
        if (root->right != NULL)
        {
            data->push_back('(');
            preOrder(root->right, data);
            data->push_back(')');
        }
        // Time = 0(n)
    }
    string tree2str(TreeNode *root)
    {
        string data = "";
        preOrder(root, &data);
        return data;
    }
};
// Helper function to create a binary tree from an array representation
TreeNode *createBinaryTree(const std::vector<int> &arr, int i)
{
    if (i >= arr.size() || arr[i] == -1)
        return nullptr;

    TreeNode *root = new TreeNode(arr[i]);
    root->left = createBinaryTree(arr, 2 * i + 1);
    root->right = createBinaryTree(arr, 2 * i + 2);
    return root;
}
int main()
{
    // Test case: [1, 2, 3, 4]
    std::vector<int> arr = {1, 2, 3, -1, 4};
    TreeNode *root = createBinaryTree(arr, 0);

    Solution solution;
    std::string result = solution.tree2str(root);

    std::cout << "Constructed String: " << result << std::endl;

    return 0;
}