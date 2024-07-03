#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        data = 0;
        next = nullptr;
    }
};
Node *removeDuplicates(Node *head)
{
    Node *prev = nullptr;
    Node *current = head;
    while (current != nullptr)
    {
        bool repitionOccurs = false;
        while (current->next != nullptr and current == current->next)
        {
            repitionOccurs = true;
            Node *nextNode = current->next;
            current->next = nextNode->next;
            free(nextNode);
        }
        if (repitionOccurs)
        {
            prev = current->next;
            current = prev;
        }
    }
}
int main()
{
    Node *A = new Node();
}