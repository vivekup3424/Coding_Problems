// Linked list implementation in C++

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define null NUll

// Creating a node
class Node {
  public:
  int value;
  Node* next;
};

//Creating a linkedList
class linkedList
{
  public:
  Node *head;
};

//Inserting a node at the start
void push(Node **head,int new_data)
{
  Node *new_node = new Node();  //1
  new_node->value = new_data;   //2
  new_node->next = (*head); //3
  (*head) = new_node; //4
}

//Inserting between two node
void insertAfter(Node *prev_node,int new_data)
{
  if (prev_node == NULL)
  {
    printf("Previous Node can't be empty.\n"); //1
  }
  
  Node *new_node = new Node();//2
  new_node->value = new_data;//3
  new_node->next = prev_node->next;  //4
  prev_node->next = new_node;   //5
}

//Inserting a node at last
void append(Node** head_ref, int new_data)
{
  // 1. allocate node
    Node* new_node = new Node();
   
    // Used in step 5
    Node *last = *head_ref;
   
    // 2. Put in the data
    new_node->value = new_data; 
   
    // 3. This new node is going to be 
    // the last node, so make next of 
    // it as NULL
    new_node->next = NULL; 
   
    // 4. If the Linked List is empty,
    // then make the new node as head
    if (*head_ref == NULL) 
    { 
        *head_ref = new_node; 
        return; 
    } 
   
    // 5. Else traverse till the last node
    while (last->next != NULL)
    {
        last = last->next; 
    }
    // 6. Change the next of last node
    last->next = new_node; 
    return; 
}

//Deleting a node
void deleteNode(Node **head_ref,int key)
{
  //Store head node
  Node *temp = *head_ref;
  Node *prev = NULL;

  // If head node itself holds
  // the key to be deleted
  if(temp!=NULL && temp->value == key)
  {
    *head_ref = temp->next; //change head
    delete temp;  //free old head
    return;
  }
  else
  {
    while (temp!=NULL &&temp->value!=key)
    {
      prev = temp;
      temp = temp->next;
    }
    if (temp==NULL)
    {
      return ;
    }
    prev->next = temp->next;
    delete temp;
  }
}

//Deleting at a given position
void deleteNode(Node** head_ref, int position)
{
 
    // If linked list is empty
    if (*head_ref == NULL)
        return;
 
    // Store head node
    Node* temp = *head_ref;
 
    // If head needs to be removed
    if (position == 0) {
 
        // Change head
        *head_ref = temp->next;
        // Free old head
        free(temp);
        return;
    }
 
    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->next;
 
    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL)
        return;
 
    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    Node* next = temp->next->next;
 
    // Unlink the node from linked list
    free(temp->next); // Free memory
 
    // Unlink the deleted node from list
    temp->next = next;
}
// This function prints contents of linked
// list starting from the given node


void printList(Node* node)
{
    while (node != NULL) {
        cout << node->value << " ";
        node = node->next;
    }
}
int main() 
{
  Node* head;
  Node* one = NULL;
  Node* two = NULL;
  Node* three = NULL;

  // allocate 3 nodes in the heap
  one = new Node();
  two = new Node();
  three = new Node();

  // Assign value values
  one->value = 1;
  two->value = 2;
  three->value = 3;

  // Connect nodes
  one->next = two;
  two->next = three;
  three->next = NULL;

  //initialize a linkedlist 
  linkedList *list = new linkedList();
  list->head = one;

  // print the linked list value
  head = one;
  while (head != NULL) {
    cout << head->value;
    head = head->next;
  }
}