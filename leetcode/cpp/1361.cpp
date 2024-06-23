
#include <bits/stdc++.h>
using namespace std;
/**
 * Properties of Binary Tree
 * 1. binary tree has only one root, that means one node has indegree = 0
 * 2. all other nodes will have indegree = 1
 * 3. from roots, all nodes can be traversed exactly once, which means there is no cycle and the indegree = 1
 * 4. for a tree of n nodes, there should be n-1 edges
 *
 * can I use these properties for my advantage??
 * may be I should calculate the indegree or number of parents of a node, hence if there
 * exists one node with 0 indegree exactly and other nodes have indgree of 1, then it is a binary tree
 */
class Solution1
{
public:
    bool validateBinaryTreeNodes(int n, vector<int> &leftChild, vector<int> &rightChild)
    {
        vector<int> indegree(n, 0);
        bool result = true;
        for (int i = 0; i < n; i++)
        {
            if (leftChild[i] != -1)
            {
                indegree[leftChild[i]]++;
            }
            if (rightChild[i] != -1)
            {
                indegree[rightChild[i]]++;
            }
        }
        int numberOfRootNodes = 0, number_of_nodes_with_multiple_indegree = 0;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                numberOfRootNodes++;
            }
            else if (indegree[i] > 1)
            {
                number_of_nodes_with_multiple_indegree++;
            }
        }
        return numberOfRootNodes == 1 and number_of_nodes_with_multiple_indegree == 0;
    }
    // this solution is not complete as its failing on the testcase
    /*
    Input
n =
4
leftChild =
[1,0,3,-1]
rightChild =
[-1,-1,-1,-1]
Use Testcase
Output
true
Expected
false*/
};
class Solution
{
public:
    bool validateBinaryTreeNodes(int n, vector<int> &leftChild, vector<int> &rightChild)
    {
        vector<int> indegree(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (leftChild[i] != -1)
            {
                indegree[leftChild[i]]++;
            }
            if (rightChild[i] != -1)
            {
                indegree[rightChild[i]]++;
            }
        }

        int root = -1;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                root = i;
                break;
            }
        }

        if (root == -1)
            return false;

        vector<bool> visited(n, false);
        stack<int> s;
        s.push(root);
        visited[root] = true;

        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (leftChild[node] != -1)
            {
                if (visited[leftChild[node]])
                    return false;
                s.push(leftChild[node]);
                visited[leftChild[node]] = true;
            }

            if (rightChild[node] != -1)
            {
                if (visited[rightChild[node]])
                    return false;
                s.push(rightChild[node]);
                visited[rightChild[node]] = true;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
                return false;
        }
        return true;
    }
};
/*

Explanation:

- Calculate indegrees to find root node
- Do a DFS traversal starting from root
- If a node is visited again, there is a cycle, return false
- After DFS, if any node is unvisited, return false
- Otherwise, it is a valid binary tree, return true

The key is to use DFS along with visited array to detect any cycles in the tree structure.*/
int main()
{
    int n = 4;
    vector<int> leftChild = {1, 0, 3, -1};
    vector<int> rightChild = {-1, -1, -1, -1};
    Solution A = Solution();
    bool r = A.validateBinaryTreeNodes(n, leftChild, rightChild);
    return 0;
}