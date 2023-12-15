#include <bits/stdc++.h>
using namespace std;
class Node
{
    public:
    int data;
    Node *next;
};

//Adding a node to the front
/*This is a 4 step process*/
void push(Node *head,int new_data)
{
    /* 1. allocate node */
    Node *new_node = new Node();

    /*2.Put data in the input*/
    new_node->data = new_data;

    /* 3.Make new_node as the head node */
    new_node->next = head;

    /*4.Move the head to point to the new_node*/
    head = new_node;
    //O(1) time and space complexity
}

//Adding node after a given node:(5 steps process)
void insertAfter(Node *prev_node,int new_data)
{
    /*1.Check is prev_node is null*/
    if(!prev_node){printf("Previous node can't be Null.\n");}

    //2.Allocate new_node
    Node *new_node = new Node();

    //3.Put data in the new_node
    new_node->data = new_data;

    //4.Make next of new node as 
    //next of prev_node
    new_node->next = prev_node->next;

    //5.Move the next of prev_node as new node
    prev_node->next = new_node;

    //O(1) is time and space compleity
}

//Add node at the end:(6 step process)
void apppend(Node *head,int new_data)
{
    Node *temp = head;
    //1.Allocate node
    Node *new_node = new Node();

    //2.Put data in the new_node
    new_node->data = new_data;

    //3.new_node is last node
    new_node->next = NULL;

    //traverse till lst node
    if (temp)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    return;
    /*O(n) is time complexity and O(1) is space complexity*/
}
int main()
{

}