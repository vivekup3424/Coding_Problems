# Definition for singly-linked list.
 class ListNode:
     def __init__(self, val=0, next=None):
         self.val = val
         self.next = next
class Solution:
    def removeNodes(self, head: ListNode) -> Optional[ListNode]:
        #using a monotonic stack
        stk = []
        temp = head
        while temp != None:
            stk.append(temp)
            while len(stk)>0 and stk   