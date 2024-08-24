#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        map<int, Node *> clonedNodes;
        // BFS
        queue<Node *> q;
        q.push(node);
        clonedNodes[node->val] = new Node(node->val);
        while (q.size() > 0)
        {
            Node *current = q.front();
            q.pop();
            for (auto neighbor : current->neighbors)
            {
                if (clonedNodes.find(neighbor->val) == clonedNodes.end())
                {
                    clonedNodes[neighbor->val] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                clonedNodes[current->val]->neighbors.push_back(clonedNodes[neighbor->val]);
            }
        }
        return clonedNodes[node->val];
    }
};