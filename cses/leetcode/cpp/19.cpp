
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // Create a dummy node to handle the case when the head needs to be removed.
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *first = dummy;
        ListNode *second = dummy;

        // Move first n+1 steps ahead.
        for (int i = 0; i <= n; i++)
        {
            first = first->next;
        }

        // Move first and second together until first reaches the end.
        while (first != nullptr)
        {
            first = first->next;
            second = second->next;
        }

        // Remove the nth node.
        second->next = second->next->next;

        return dummy->next; // Return the updated head.
    }
};

int main()
{
}