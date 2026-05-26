class Node {
    Node next;
    Node prev;
    int data;

    Node(int _data) {
        data = _data;
        next = null;
        prev = null;
    }
}

public class StackWithOperationsOnMiddleElement {
    Node head;
    Node mid;
    int size;

    StackWithOperationsOnMiddleElement() {
        head = null;
        mid = null;
        size = 0;
    }

    // mid tracks position ceil(size/2) from head (1-indexed)
    void push(int data) {
        size++;
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
            mid = newNode;
            return;
        }
        newNode.next = head;
        head.prev = newNode;
        head = newNode;
        // when size becomes even, mid shifts one step toward head
        if (size % 2 == 0) mid = mid.prev;
    }

    int pop() {
        if (head == null) return -1;
        // when size is even, removing head shifts mid one step toward tail
        if (size % 2 == 0) mid = mid.next;
        size--;
        int data = head.data;
        head = head.next;
        if (head != null) head.prev = null;
        return data;
    }

    int popMiddle() {
        if (head == null) return -1;
        int data = mid.data;
        Node newMid = (size % 2 == 1) ? mid.prev : mid.next;
        if (mid.prev != null) mid.prev.next = mid.next;
        else head = mid.next;
        if (mid.next != null) mid.next.prev = mid.prev;
        mid = newMid;
        size--;
        return data;
    }
}
