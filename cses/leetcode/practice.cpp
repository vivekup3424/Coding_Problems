
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int x) : data(x), next(nullptr) {}
    Node(int x, Node *next) : data(x), next(next) {}
};

Node *constructLL(vector<int> &arr)
{
    Node *head = new Node();
    Node *current = head;
    for (int num : arr)
    {
        Node *temp = new Node(num);
        current->next = temp;
        current = current->next;
    }
    return head->next;
}
int main()
{
}