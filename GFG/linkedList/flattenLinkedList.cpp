#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node * next;
    struct Node * bottom;

    Node(int x){
        data = x;
        next = NULL;
        bottom = NULL;
    }

};

Node *mergeList(Node *headA, Node *headB){
    auto head = new Node(-1);
    auto temp = head;
    while(headA!=nullptr and headB!=nullptr){
        if(headA->data < headB->data){
            auto newNode = new Node(headA->data);
            temp->bottom = newNode;
            temp = newNode;
            headA = headA->bottom;
        }else{
            auto newNode = new Node(headB->data);
            temp->bottom = newNode;
            temp = newNode;
            headB = headB->bottom;
        }
    }
    if(headA!=nullptr){
        temp->bottom = headA;
    }
    if(headB!=nullptr){
        temp->bottom = headB;
    }
    return head->bottom;
}

Node *mergeKLists(Node *head){
    if(head == nullptr||head->next == nullptr){
        return head;
    }
    head->next = mergeKLists(head->next);
    head = mergeList(head, head->next);
    return head;
}
