#include <bits/stdc++.h>
using namespace std;
/*Inserting node in Doubly Linked List*/
class Node
{
    public:
    int data;
    Node *next; //pointer to next node in DLL
    Node *prev; //pointer to previous node in DLL
};
/*1) Add a node at the front: (A 5 steps process) */
void push(Node *head,int new_data)
{
    //1.Allocate node
    Node *new_node = new Node();
    //2.put in the data
    new_node->data = new_data;
    //3.next of new_node as head
    new_node->next = head;
    new_node->prev = NULL;
    /* 4. change prev of head node to new node */
    head->prev = new_node;
    /*5.move the head to new_node*/
    head = new_node;
}

void insertAfter(Node* prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        cout<<"the given previous node cannot be NULL";
        return;
    }
 
    /* 2. allocate new node */
    Node* new_node = new Node();
 
    /* 3. put in the data */
    new_node->data = new_data;
 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
 
    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;
 
    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;
 
    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
    new_node->next->prev = new_node;
}

/*3) Add a node at the end: (7 steps process) */
void append(Node *head,int new_data)
{
    /* 1. allocate node */
    Node* new_node = new Node();
 
    Node* temp = head; /* used in step 5*/
 
    /* 2. put in the data */
    new_node->data = new_data;
 
    /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new
        node as head */
    if (head == NULL)
    {
        new_node->prev = NULL;
        head = new_node;
        return;
    }
    /* 5. Else traverse till the last node */
    while (temp->next != NULL)
        temp = temp->next;
 
    /* 6. Change the next of last node */
    temp->next = new_node;
 
    /* 7. Make last node as previous of new node */
    new_node->prev = temp;
 
    return;
}