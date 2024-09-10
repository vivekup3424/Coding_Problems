#include <bits/stdc++.h>
using namespace std;
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    
    ListNode *insertGreatestCommonDivisors(ListNode* head) {
       ListNode *temp = head;
       while(temp->next!=NULL)
       {
        ListNode *tempNext = temp->next;
        int a = temp->val;
        int b = temp->next->val;
        int c = __gcd(a,b);
        ListNode *newNode = new ListNode(c);
        newNode->next = tempNext;
        temp->next = newNode;
        temp = tempNext;
       }
       return head; 
    }
};
