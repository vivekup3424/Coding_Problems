
#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *findCollision(ListNode *t1, ListNode *t2)
    {
        /**
         * @returns collision of the two nodes
         */
        while (t1 != t2)
        {
            t1 = t1->next;
            t2 = t2->next;
        }
        return t1;
    }
    ListNode *detectCycle(ListNode *head)
    {
        // detect cylce, if no cycle return nullptr
        ListNode *fast = head, *slow = head;
        while (fast != nullptr and fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
            {
                // if cycle exists, then find the collision point
                slow = head;
                ListNode *result = findCollision(slow, fast);
                return result;
            }
        }
        return nullptr;
    }
};
int main()
{
}