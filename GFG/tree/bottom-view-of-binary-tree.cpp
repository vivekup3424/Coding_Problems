#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};
class Solution
{
public:
    vector<int> bottomView(Node *root)
    {
        queue<pair<int, Node *>> q;
        map<int, int> mp;
        vector<int> v;
        if (root == nullptr)
        {
            return v;
        }
        q.push({0, root});
        while (!q.empty())
        {
            auto level = q.front().first;
            auto node = q.front().second;
            q.pop();
            mp[level] = node->data;
            if (node->left != nullptr)
            {
                q.push({level - 1, node->left});
            }
            if (node->right != nullptr)
            {
                q.push({level + 1, node->right});
            }
        }
        for (auto it : mp)
        {
            v.push_back(it.second);
        }
        return v;
    }
};