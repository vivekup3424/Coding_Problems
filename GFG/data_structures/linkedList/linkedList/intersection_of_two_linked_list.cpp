/**
 * Given the heads of two singly linked-lists headA and headB,
 * return the node at which the two lists intersect.
 * If the two linked lists have no intersection at all, return null.
 */

#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// Method 1 :- using some hash set data structure to store the visited nodes
// Method 2:-Using constant extra space
class Solution1
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        unordered_set<ListNode *> s;
        ListNode *temp = headA;
        while (temp != nullptr)
        {
            s.insert(temp);
            temp = temp->next;
        }

        ListNode *res = new ListNode(0);
        temp = headB;
        while (temp != nullptr)
        {
            if (s.count(temp) != 0)
            {
                res = temp;
                return res;
            }
            else
            {
                temp = temp->next;
            }
        }
        return nullptr;
    }
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        /**
         * Compute the length of first linked list, and then length of second linked list
         * Make trim the longer linked list to the length of the smaller linked list
         * then do a step-by-step comparison
         *
         */

        int l1 = 0, l2 = 0;
        ListNode *temp1 = headA, *temp2 = headB;
        while (temp1 != NULL)
        {
            l1++;
            temp1 = temp1->next;
        }
        while (temp2 != NULL)
        {
            l2++;
            temp2 = temp2->next;
        }
        temp1 = headA;
        temp2 = headB;
        while (l1 > 0 and l2 > 0)
        {
            if (temp1 == temp2)
            {
                return temp1;
            }
            else if (l1 > l2)
            {
                temp1 = temp1->next;
                l1--;
            }
            else
            {
                temp2 = temp2->next;
                l2--;
            }
        }
        return nullptr;
    }
};
int main()
{
}