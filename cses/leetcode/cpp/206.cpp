
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
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr, *current = head;
        while (current != NULL)
        {
            ListNode *temp = current->next; // saving the immediate data in a data register
            current->next = prev;
            prev = current;
            current = temp;
        }
        return prev;
    }
};
int main()
{
}