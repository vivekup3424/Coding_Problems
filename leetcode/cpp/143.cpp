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
        //store the list in a vector
        vector<int> v;
        ListNode *temp = head;
        while(temp!=nullptr){
            v.push_back(temp->val);
            temp = temp->next;
        }
        int i = 0, j = v.size()-1;
        ListNode *head1 = nullptr;
        while(i<j){
            if(i==0){
                ListNode *head1 = new ListNode(v[i]);
                temp = head1;
            }
            else if(i > 0){
                ListNode *newNode = new ListNode(v[i]);
                temp->next = newNode;
                temp = newNode;
            }
            i++;
            ListNode *newNode = new ListNode(v[j]);
            temp->next = newNode;
            j--;
            temp = newNode;
        }
        return head1;
    } 
};
