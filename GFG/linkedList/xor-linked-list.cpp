#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

struct Node{
    int data;
    struct Node *npx;
    Node(int x){
        data = x;
        npx = nullptr;
    }
};
struct Node *XOR(Node *a, Node *b){
    return (Node *) ((uintptr_t)a ^ (uintptr_t)b);
}
struct Node *insert(struct Node *head, int data){
    Node *newNode = new Node(data);
    Node *temp = head;
    if(head==nullptr){
        return newNode;
    }
    while(temp->npx != nullptr){
        temp = temp->npx;
    }
    temp->npx = newNode;
    return head;
}
vector<int> getList(struct Node *head){
    vector<int> v;
    auto temp = head;
    while(temp!=nullptr){
        v.push_back(temp->data);
        temp = temp->npx;
    }
    return v;
}
int main(){
    
}
