// given a doubly linked list, write the code to reverse it and return the head of the doubly linked list

#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *prev;
    Node *next;
    Node(int x = 0)
    {
        this->data = x;
        this->prev = nullptr;
        this->next = nullptr;
    }
};
/**
 * Method 1:- Using stack to hold the value while traversing, and then placing the value in reverse order
 * using stack
 */
Node *reverse1(Node *head)
{
    stack<int> stk;
    Node *temp = head;
    // making stack
    while (temp != nullptr)
    {
        stk.push(temp->data);
        temp = temp->next;
    }

    // reverse using first in lost out order
    temp = head;
    while (temp != NULL)
    {
        temp->data = stk.top();
        stk.pop();
        temp = temp->next;
    }
    return head;
    // Time complexity = O(n)
    // Auxilliary Space(extra space required) = O(n) //stack //space complexity
}

/**
 * Method 2:- Using single pass, by modifying the modifers in place of data
 */
Node *reverse2(Node *head)
{
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL)
    {
        current->prev = current->next;
        current->next = prev;
        prev = current;
        current = current->prev;
    }
    return prev;
    // Time Complexity = O(n)
    // Space Complexity O(1)
}
int main()
{
}