#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.*/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *reverse(ListNode *head)
    {
        ListNode *prevNode = nullptr,
                 *current = head;
        while (current != nullptr)
        {
            ListNode *temp = current->next;
            current->next = prevNode;
            prevNode = current;
            current = temp;
        }
        return prevNode;
    }
    ListNode *doubleIt0(ListNode *head)
    {
        int number;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            number = 10 * number + (temp->val + '0');
        }
        cout << "Number = " << number << endl;
        number = 2 * number;
        ListNode
    }
    // 1.reverse the linkedlist and then double it
    ListNode *doubleIt1(ListNode *head)
    {
        ListNode *reversedNode = reverse(head);
        // start doubling the shit
        int carry = 0;
        ListNode *temp = reversedNode;
        ListNode *prevNode = nullptr;
        while (temp != nullptr)
        {
            temp->val = 2 * temp->val + carry;
            carry = temp->val / 10;
            temp->val = temp->val % 10;
            prevNode = temp;
            temp = temp->next;
        }
        if (temp == nullptr and carry > 0)
        {
            ListNode *newNode = new ListNode(carry);
            prevNode->next = newNode;
            delete temp;
        }
        ListNode *ans = reverse(reversedNode);
        return ans;
    }
};