//Remove duplicates from a sorted linked list
#include <iostream>
using namespace std;
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
void removeDuplicates(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    
    Node *temp = head;
    while(temp->next!=NULL)
    {
        if(temp->value == temp->next->value)
        {
            Node *next_next;
            next_next = temp->next->next;
            free(temp->next);
            temp->next = next_next;
        }
        else    /* This is tricky: only advance if no deletion */
        {
            temp = temp->next;
        }
    }
}

/* UTILITY FUNCTIONS */
/* Function to insert a node at the beginning of the linked list*/
void push(Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node = new Node();
             
    /* put in the data */
    new_node->value = new_data;
                 
    /* link the old list off the new node */
    new_node->next = (*head_ref);    
         
    /* move the head to point to the new node */
    (*head_ref) = new_node;
}
 
/* Function to print nodes in a given linked list */
void printList(Node *node)
{
    while (node!=NULL)
    {
        cout<<" "<<node->value;
        node = node->next;
    }
}

/* Driver program to test above functions*/
int main()
{
    /* Start with the empty list */
    Node* head = NULL;
     
    /* Let us create a sorted linked list to test the functions
    Created linked list will be 11->11->11->13->13->20 */
    push(&head, 20);
    push(&head, 13);
    push(&head, 13);
    push(&head, 11);
    push(&head, 11);
    push(&head, 11);                                    
 
    cout<<"Linked list before duplicate removal ";
    printList(head);
 
    /* Remove duplicates from linked list */
    removeDuplicates(head);
 
    cout<<"\nLinked list after duplicate removal ";    
    printList(head); 
     
    return 0;
}