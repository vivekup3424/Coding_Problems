#include <bits/stdc++.h>
using namespace std;
class Node
{
    public:
    int data;
    Node *next;
    Node *prev;
};
void reverse(Node *head)
{
    Node *temp = new Node();
    Node *current = head;
    while(current!=NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if(!temp)
    {
        head = temp->prev;
    }
}