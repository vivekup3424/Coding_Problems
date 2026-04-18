public class LinkedListNode {
    private LinkedList prev;
    private LinkedList head;
    private int data;
    LinkedListNode(int _data){
        data = _data;
    }
    public int getData() {
        return data;
    }
    public LinkedList getHead() {
        return head;
    }
    public LinkedList getPrev() {
        return prev;
    }
    public void setData(int data) {
        this.data = data;
    }
    public void setHead(LinkedList head) {
        this.head = head;
    }
    public void setPrev(LinkedList prev) {
        this.prev = prev;
    }
}