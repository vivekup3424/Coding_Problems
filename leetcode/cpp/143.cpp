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
    
    void reorderList(ListNode* head) {
        //find the middle of the linkedlist
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }
        //slow node is the middle node
        //reverse the second part
        ListNode *prev = slow;
        ListNode *current = slow->next;
        while(current!=nullptr){
            ListNode *temp = current->next;
            current->next = prev;
            prev = current;
            current = temp;
        }

        ListNode *first = head, *second = slow->next;
        bool firstConnect = true;
        while(second != nullptr){
            if(firstConnect){
                ListNode *tempFirst = first->next;
                first->next = second;
                first = tempFirst;
                firstConnect = !firstConnect;
            }
            else{
                ListNode *tempSecond = second->next;
                second->next = first;
                second = tempSecond;
                firstConnect = !firstConnect;
            }
        }
    } 
}; 
