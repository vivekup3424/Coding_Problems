
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
    ListNode *deleteMiddle(ListNode *head)
    {
        // Use a dummy node to simplify code
        ListNode dummy(0);
        dummy.next = head;

        ListNode *slow = &dummy, *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Delete middle node
        slow->next = slow->next->next;
        return dummy.next;
    }
};
int main()
{
}