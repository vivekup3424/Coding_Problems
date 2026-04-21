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
    ListNode() {}
    ListNode(int data) {this.data = data;}
    ListNode(int data, ListNode next){}
}
public class DesignHashset {
    ListNode head;
    DesignHashset(){
        head = null;
    }
    
    public void add(int data){
        ListNode node = new ListNode(data);
        if(head==null) head = node;
        else{
            head.next = node;
        }
    }

    public boolean contains(int data){
        if(head==null) return false;
        ListNode temp = head;
        while(temp!=null){
            if(temp.data == data) return true;
            temp = temp.next;
        }
        return false;
    }

    public void remove(int data){
        if(head == null) return;
        
    }
    
}