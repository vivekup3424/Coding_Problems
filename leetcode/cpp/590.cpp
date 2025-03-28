#include <bits/stdc++.h>
using namespace std;
// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    void recurse(Node *root, vector<int> &v)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            for (int i = 0; i < root->children.size(); i++)
            {
                recurse(root->children[i], v);
            }
            v.push_back(root->val);
        }
    }
    vector<int> postorder(Node *root)
    {
        vector<int> v;
        recurse(root, v);
        return v;
    }
};