#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Definition for singly-linked list.*/
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
    int numComponents(ListNode *head, vector<int> &nums)
    {
        int n = nums.size();
        vector<bool> visited(n, false);
        int components = 0;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            int val = temp->val;
            for (int i = 0; i < n; i++)
            {
                if (val == nums[i] && visited[i] == false)
                {
                    visited[i] = true;
                    int j = i - 1, k = i + 1;
                    while (j >= 0 and visited[j] == false)
                    {
                        if (temp->next !=)
                    }
                }
            }
        }
    }
};