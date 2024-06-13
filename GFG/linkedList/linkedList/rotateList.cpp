
#include <bits/stdc++.h>
using namespace std;
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
    ListNode *findNthNode(ListNode *head, int N)
    {
        int count = 1;
        ListNode *temp = head;
        while (temp != NULL)
        {
            if (count == N)
                return temp;
            else
            {
                temp = temp->next;
                count++;
            }
        }
        return temp;
    }
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == NULL)
            return head; // edge case
        int length = 1;
        ListNode *tail = head;
        while (tail->next != NULL)
        {
            tail++;
            tail = tail->next;
        }
        k = k % length;
        if (k == 0)
            return head; // edge case

        int diff = length - k;
        ListNode *newLastNode = findNthNode(head, diff);
        ListNode *newHead = newLastNode->next;
        newLastNode->next = NULL;
        return newHead;
    }
};
int main()
{
}