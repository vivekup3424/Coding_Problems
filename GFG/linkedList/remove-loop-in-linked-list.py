class Node:
    def __init__(self,_val):
        self.next = None
        self.val = _val

class Solution:
    def remove(self,head):
        if head is None or head.next is None:
            return False
        slow = head
        fast = head
        #slow moves 1 step
        #fast moves 2 step
        while slow and fast and fast.next:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                slow = head
