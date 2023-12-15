/*I am going to try and implement a circular linked list
example*/
#include <iostream>
using namespace std;
class Node
{
    public:
    int data;
    Node *next;
};

/* Function to print nodes in
a given Circular linked list */
void printList(Node* head)
{
	Node* temp = head;

	// If linked list is not empty
	if (head != NULL) {

		// Print nodes till we reach first node again
		do {
			cout << temp->data << " ";
			temp = temp->next;
		} while (temp != head);
        cout << endl;
	}
}

/* Function to insert a node at the beginning
of a Circular linked list */
void push(Node *head_ref, int data)
{
    Node *ptr1 = new Node();
    Node *temp = head_ref;
    ptr1->data = data;
    ptr1->next = head_ref;
 
    /* If linked list is not NULL then
    set the next of last node */
    if (head_ref != NULL)
    {
        while (temp->next != head_ref)
            temp = temp->next;
        temp->next = ptr1;
    }
    else
        ptr1->next = ptr1; /*For the first node */
 
    head_ref = ptr1;
}
void Push(Node *head_ref,int new_data)
{
    Node *ptr1 = new Node();
    ptr1->data = new_data;
    if (head_ref == NULL)
    {
        ptr1->next = ptr1;
    }
    else
    {
        ptr1->next = head_ref;
        Node *temp = new Node();
        temp = head_ref;
        do
        {
            temp = temp->next;
        } while (temp->next!=head_ref);
        temp->next = ptr1;
    }
}
int main()
{
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();
    Node *fourth = new Node();
    head->data = 1;
    second->data = 2;
    third->data = 3;
    fourth->data = 4;
    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = head;
    /*an instance of a circular linked list*/

    Push(head, 12);
    Push(head, 56);
    Push(head, 2);
    Push(head, 11);

    cout << "Contents of Circular Linked List\n ";
    printList(head);
}