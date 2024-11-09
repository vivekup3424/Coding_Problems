#include <bits/stdc++.h>
#include <functional>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        unordered_map<Node*, Node*> mp;

        // First pass: create new nodes and map original nodes to new nodes
        Node* current = head;
        while (current) {
            mp[current] = new Node(current->val);
            current = current->next;
        }

        // Second pass: link next and random pointers of new nodes
        current = head;
        while (current) {
            Node* newNode = mp[current];
            newNode->next = mp[current->next];
            newNode->random = mp[current->random];
            current = current->next;
        }

        // Return the head of the copied list
        return mp[head];
    }
};
