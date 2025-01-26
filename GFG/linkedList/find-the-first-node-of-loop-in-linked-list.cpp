#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
    Node(int x){
        data = x;
        next = nullptr;
    }
};
class Solution{
    public:
    Node *findfirstNode(Node *head){
        set<Node*> visited;
        Node *temp = head;
        while(temp!=nullptr){
            if(visited.find(temp) != visited.end()){
                return temp;
            }
            visited.insert(temp);
            temp = temp->next;
        }
        return nullptr;
    }
}