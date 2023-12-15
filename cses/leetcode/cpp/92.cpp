
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
    ListNode *reverseList(ListNode *left, ListNode *right)
    {
        ListNode *prev = NULL;
        ListNode *curr = left;
        while (curr != right->next)
        {
            ListNode *data = curr->next;
            curr->next = prev;
            prev = curr;
            curr = data;
        }
        return prev;
    }
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        // find the inclusive leftNode and rightNode
        int index = 1;
        ListNode *temp = head;
        ListNode *leftNode = nullptr, *rightNode = nullptr, *beforeLeftNode, *afterRightNode;
        while (temp != NULL)
        {
            if (index == left - 1 and left)
            {
            }
        }
    }
};
int main()
{
}