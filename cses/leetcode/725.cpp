
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
    vector<ListNode *> splitListToParts(ListNode *head, int k)
    {
        int length = 0;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            length++;
            temp = temp->next;
        }
        int parts = length / k, extra_One_parts = length % k;
        vector<ListNode *> results;
        temp = head; // Reinitialize the pointer to the head

        while (parts--)
        {
            ListNode *result = nullptr;
            ListNode *t = result;
            for (int i = 0; i < k + (extra_One_parts > 0 ? 1 : 0); i++)
            {
                if (temp != nullptr)
                {
                    result = new ListNode(temp->val, temp->next);
                    result = result->next;
                    temp = temp->next;
                }
            }
            extra_One_parts--;
            results.push_back(t);
        }
        return results;
    }
};

int main()
{
}