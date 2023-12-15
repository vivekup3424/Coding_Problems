
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
    ListNode *mergeNodes(ListNode *head)
    {
        ListNode *dummy = new ListNode(0);
        ListNode *temp = dummy;
        bool state = false; // false signfies that we have to make a new node
        // true = new node has been added and we are further adding the values;
        while (head != nullptr)
        {
            if (head->val == 0 and state == false)
            {
                state = true;
                temp->next = new ListNode(0); // made a new node
                temp = temp->next;
            }
            else if (head->val != 0 and state == true) // since its true we can add values herer
            {
                // state unchanged
                temp->val += head->val;
            }
            else if (head->next == NULL and head->val == 0)
            {
                break;
            }
            else if (head->val == 0 and state == true)
            {
                state = true;
                temp->next = new ListNode(0); // make a new node
                temp = temp->next;
            }
            head = head->next;
        }
        ListNode *result = dummy->next;
        delete dummy;
        return result;
    }
};
int main()
{
    // Create the input linked list
    ListNode *head = new ListNode(0);
    head->next = new ListNode(3);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(0);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next->next = new ListNode(0);

    // Create an instance of the Solution class
    Solution solution;

    // Call the mergeNodes function
    ListNode *result = solution.mergeNodes(head);

    // Print the output linked list
    while (result != nullptr)
    {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;

    // Don't forget to clean up memory
    while (head != nullptr)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}