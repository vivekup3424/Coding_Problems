public class TwoStacksInArray {
    private int[] arr;
    private int idx1, idx2;
    TwoStacksInArray() {
        arr = new int[100];
        idx1 = -1;
        idx2 = 100;
    }

    // Function to push an integer into the stack1.
    void push1(int x) {
        if(idx2 - idx1 == 1) throw new RuntimeException("stack overflow");
        arr[++idx1] = x;
    }

    // Function to push an integer into the stack2.
    void push2(int x) {
        if(idx2 - idx1 == 1) throw new RuntimeException("stack overflow");
        arr[--idx2] = x;
    }

    // Function to remove an element from top of the stack1.

    int pop1() {
        if (idx1 < 0)  throw new RuntimeException("stack underflow");
        return arr[idx1--];
    }

    // Function to remove an element from top of the stack2.
    int pop2() {
        if(idx2 >= arr.length) throw new RuntimeException("stack underflow");
        return arr[idx2++];
    }
};
