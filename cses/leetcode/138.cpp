
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        unordered_map<int, Node *> mp;
        Node *start = new Node(0);
        Node *temp = start;
        while (head != NULL)
        {
            if (mp.find(head->val) == mp.end())
            {
                start->next = new Node(head->val);
                if (head->random != nullptr)
                {
                    start->random = new Node(head->random->val);
                }
                else
                {
                    start->random = nullptr;
                }
                mp[start->val] = start->random;
                start = start->next;
            }
            head = head->next;
        }
        return temp->next;
    }
};
int main()
{
    // Create the nodes
    Node *node7 = new Node(7);
    Node *node13 = new Node(13);
    Node *node11 = new Node(11);
    Node *node10 = new Node(10);
    Node *node1 = new Node(1);

    // Set up the next pointers
    node7->next = node13;
    node13->next = node11;
    node11->next = node10;
    node10->next = node1;

    // Set up the random pointers
    node7->random = nullptr;
    node13->random = node7;
    node11->random = node1;
    node10->random = node11;
    node1->random = node7;

    Solution solution;
    Node *copy = solution.copyRandomList(node7);

    // Print the copied list and random pointers
    while (copy)
    {
        cout << "[" << copy->val << ",";
        if (copy->random)
        {
            cout << copy->random->val << "]";
        }
        else
        {
            cout << "null]";
        }
        if (copy->next)
        {
            cout << " -> ";
        }
        copy = copy->next;
    }

    // Clean up memory (don't forget to free the original list too)
    while (node7)
    {
        Node *temp = node7;
        node7 = node7->next;
        delete temp;
    }

    return 0;
}