/**
 * Design a HashSet without using any built-in hash table libraries.

Implement MyHashSet class:

    void add(key) Inserts the value key into the HashSet.

    bool contains(key) Returns whether the value key exists in the 
    HashSet or not.

    void remove(key) Removes the value key in the HashSet. If key 
    does not exist in the HashSet, do nothing.

 */

class ListNode{
    int data;
    ListNode next;
    ListNode(int data) {this.data = data;}
}
class MyHashset {
    public final int MAX_LENGTH = 10000;
    public ListNode[] values;
    public MyHashset(){
        values = new ListNode[MAX_LENGTH];
    }
    
    public void add(int data){
        if(contains(data)) return;
        int idx = data % MAX_LENGTH;
        ListNode head = values[idx];
        ListNode newNode = new ListNode(data);
        newNode.next = head;
        head = newNode;
    }

    public boolean contains(int data){
        int idx = data % MAX_LENGTH;
        ListNode head = values[idx];
        if(head==null) return false;
        ListNode temp = head;
        while(temp!=null){
            if(temp.data == data) return true;
            temp = temp.next;
        }
        return false;
    }

    public void remove(int data){
        int idx = data % MAX_LENGTH;
        ListNode head = values[idx];
        if(head == null) return;
        if(head.data == data){
            head = head.next;
            return;
        }
        ListNode prev = null;
        ListNode temp = head;
        while(temp!=null){
            if(temp.data == data){
                prev.next = temp.next;
                break;
            }
            prev = temp;
            temp = temp.next;
        }
    }
    
}