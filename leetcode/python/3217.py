class Solution:
    def modifiedList(self, v, head):
        dummy = ListNode(-1)
        t = dummy
        s = set(v)
        
        while head:
            if head.val not in s:
                t.next = head
                t = t.next
            head = head.next
        
        t.next = None
        return dummy.next