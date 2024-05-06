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
    ListNode *removeNodes(ListNode *head)
    {
        // traverse the linked list
        vector<int> v;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            v.push_back(temp->val);
            temp = temp->next;
        }
        reverse(v.begin(), v.end());
        // print the vector
        vector<int> ans;
        int maxi = v[0];
        for (int i = 0; i < v.size(); i++)
        {
            if (maxi > v[i])
                continue;
            else
            {
                ans.push_back(v[i]);
            }
            maxi = max(maxi, ans[i]);
        }
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
        reverse(ans.begin(), ans.end());
        // constructing a new linked list
        head = new ListNode();
        ListNode *p = head;
        for (int i = 0; i < ans.size(); i++)
        {
            ListNode *temp = new ListNode(ans[i]);
            p->next = temp;
            p = temp;
        }
        return head->next;
    }
};
int main()
{
    ListNode *head = new ListNode(5);
    ListNode *second = new ListNode(2);
    ListNode *third = new ListNode(13);
    ListNode *fourth = new ListNode(3);
    ListNode *fifth = new ListNode(8);
    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    Solution A;
    A.removeNodes(head);
}