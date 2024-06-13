/*Reverse a  linked list*/
#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data =  data;
        next = NULL;
    }
};
void reverse(Node *head)    //iterative
{
    Node *current = head;
    Node *prev = NULL,*next = NULL;
    while(current!=NULL)
    {
        //store next
        next =  current->next;
        //Reverse current node's pointer
        current->next = prev;
        //Move pointers one position ahead
        prev = current;
        current = next;
    }
    head = prev;
    /*Time complexity = O(n)
    Space complexity = O(1)
    */
}

/*Recursive Method: 

   1) Divide the list in two parts - first node and 
      rest of the linked list.
   2) Call reverse for the rest of the linked list.
   3) Link rest to first.
   4) Fix head pointer*/
Node *reverse_recursive(Node *head)
{
    if(head == NULL || head->next == NULL)return head;

    /*reverse the resr list and put the first element
    at the end*/
    Node *rest = reverse_recursive(head->next);
    head->next->next = head;

    head->next = NULL;

    return rest;
    /*Time Complexity: O(n)
    Space Complexity: O(1)*/
}

/*Simpler and Tail recursive Method*/

/*Using array:

Algorithm :- 

    1. Create a linked list.

    2. Count the number of nodes present in the Linked List

    3. Initialize an array with the size of the count.

    4. Store the elements of the Linked list in array 

    5. Print the array from the last index to the first.*/
    


int main()
{
    return 0;
}
