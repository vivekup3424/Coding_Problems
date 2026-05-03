class ListNode {
    int key;
    int val;
    ListNode next;

    ListNode(int key, int val) {
        this.key = key;
        this.val = val;
    }
}

class MyHashMap {
    public final int MAX_LENGTH = 10000;
    public ListNode[] values;

    public MyHashMap() {
        values = new ListNode[MAX_LENGTH];
    }

    public void put(int key, int value) {
        int idx = (MAX_LENGTH + key) % MAX_LENGTH;
        ListNode temp = values[idx];
        while (temp != null) {
            if (temp.key == key) {
                temp.val = value;
                return;
            }
            temp = temp.next;
        }
        ListNode newNode = new ListNode(key, value);
        newNode.next = values[idx];
        values[idx] = newNode;
    }

    public int get(int key) {
        int idx = (MAX_LENGTH + key) % MAX_LENGTH;
        ListNode temp = values[idx];
        if (temp == null)
            return -1;
        while (temp != null) {
            if (temp.key == key) {
                return temp.val;
            }
            temp = temp.next;
        }
        return -1;
    }
    public void remove(int key){
        int idx = (MAX_LENGTH + key) % MAX_LENGTH;
        ListNode temp = values[idx];
        if(temp == null) return;
        if(temp.key == key){
            values[idx] = temp.next;
            return;
        }
        while(temp.next != null){
            if(temp.next.key == key){
                temp.next = temp.next.next;
                return;
            }
            temp = temp.next;
        }
    }
}