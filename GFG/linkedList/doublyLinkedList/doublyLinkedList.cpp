#include <bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
void insert(struct node **head, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    *head = new_node;
}