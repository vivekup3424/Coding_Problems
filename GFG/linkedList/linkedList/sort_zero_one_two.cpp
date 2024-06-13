
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        this->data = 0;
        next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

Node *sortList(Node *head)
{
    Node *zero = new Node(-1), *one = new Node(-1), *two = new Node(-1);
    Node *oneHead = one, *twoHead = two, *zeroHead = zero;
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == 0)
        {
            zero->next = temp;
            zero = zero->next;
        }
        else if (temp->data == 1)
        {
            one->next = temp;
            one = one->next;
        }
        else if (temp->data == 2)
        {
            two->next = temp;
            two = two->next;
        }
    }
    if (oneHead->data == -1)
    {
        zero->next = twoHead->next;
    }
    else
    {
        zero->next = oneHead->next;
        one->next = twoHead->next;
    }
    if (zeroHead->next)
    {
        return zeroHead;
    }
    else if (oneHead)
    {
        return oneHead;
    }
    else
    {
        return twoHead;
    }
}
int main()
{
}