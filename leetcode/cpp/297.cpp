#include <bits/stdc++.h>
#include <sstream>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string ans;
        if (root == nullptr)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *source = q.front();
            q.pop();
            if (source == nullptr)
                ans.append("#,");
            else
                ans.append(to_string(source->val) + ',');
            if (source != nullptr)
            {
                q.push(source->left);
                q.push(source->right);
            }
        }
        cout << ans << endl;
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        if (data.size() == 0)
            return nullptr;
        stringstream s(data);
        string temp;
        getline(s, temp, ',');
        TreeNode *root = new TreeNode(stoi(temp));
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *source = q.front();
            q.pop();

            getline(s, temp, ',');
            if (str == '#')
            {
                source->left = nullptr;
            }
            else
            {
                TreeNode *newNode = new TreeNode(stoi(str));
                node->left = newNode;
                q.push(newNode);
            }
            getline(s, str, ',');
            if (str == '#')
            {
                source->right == nullptr;
            }
            else
            {
                TreeNode *newNode = new TreeNode(stoi(str));
                node->right = newNode;
                q.push(newNode);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));