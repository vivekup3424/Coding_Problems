//Remove duplicates from a sorted linked list
//Using recursion
#include <bits/stdc++.h>
using namespace std;

/*Link list Node*/
class Node
{
    public:
    int data;
    Node *next;
};
/*The function removes duplicates from a sorted using 
recursive approach*/
void removeDuplicates(Node *head)
{
    /*Pointer to store the pointer of the node to be deleted*/
    Node *to_free;

    /*do nothing if the list is empty*/
    if(head == NULL)return;

    /*else traverse the list till the last node*/
    if(head->next!=NULL)
    {
        /*Compare head node to next node*/
        if(head->data ==head->next->data)
        {
            /* The sequence of steps is important.
            to_free pointer stores the next of head
            pointer which is to be deleted.*/ 
        }
    }
}