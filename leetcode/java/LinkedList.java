class Node{
    int data;
    Node next;
    public Node(int _data){
        data = _data;
        next = null;
    }
}

class LinkedList{
    Node head;
    public void addFirst(int val){
        Node temp = new Node(val);
        temp.next = head;
        head = temp;
    }
    public void addLast(int val){
        Node temp = new Node(val);
        if(head==null){
            head = temp;
            return;
        }
        Node currentNode = head;
        while (currentNode.next!=null) {
            currentNode = currentNode.next;
        }
        currentNode.next = temp;
    }
    public void insertAfter(Node alpha, int val){
        if(alpha == null) return;
        Node temp = new Node(val);
        temp.next = alpha.next;
        alpha.next = temp;
    }
    public void print(){
        Node curr = head;
        while(curr!=null){
            System.out.println(curr.data+"->");
            curr = curr.next;
        }
        System.out.println("null");
    }
    public int removeFirst(){
        if(head==null) return -1;
        int temp = head.data;
        head = head.next;
        return temp;
    }
    public int removeLast(){
        if(head == null){
            return -1;
        }
        if(head.next == null){
            int val = head.data;
            head = null;
            return val;
        }
        Node currentNode = head;
        while(currentNode.next.next != null){
            currentNode = currentNode.next;
        }
        int temp = currentNode.next.data;
        currentNode.next = null;
        return temp;
    }
}