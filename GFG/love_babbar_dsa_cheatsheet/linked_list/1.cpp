// Write a program to reverse the linked list

// Given a pointer to the head node of a linked list,
// the task is to reverse the linked list.
// We need to reverse the list by changing the links between nodes.
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

struct linkedList
{
    Node *head;
    linkedList()
    {
        head = nullptr;
    }
    void push(int data) // push the node to the last of the linked list
    {
        Node *t = new Node(data);
        struct Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = t;
    }
    void print()
    {
        struct Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
    void reverse()
    {
        Node *prev = NULL, *current = this->head, *next = current->next;
        while (current != NULL)
        {
            // Store next
            next = current->next;
            current->next = prev;

            // Move the pointers one step ahead
            prev = current;
            current = next;
        }
        this->head = prev;
    }
};
/* Driver code*/
int main()
{
    /* Start with the empty list */
    linkedList ll;
    ll.push(20);
    ll.push(4);
    ll.push(15);
    ll.push(85);

    cout << "Given linked list\n";
    ll.print();

    ll.reverse();

    cout << "\nReversed linked list \n";
    ll.print();
    return 0;
}