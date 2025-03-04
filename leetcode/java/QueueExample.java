import java.util.*;
public class QueueExample{
    public static void main(String[] args) {
        Queue<String> queue = new LinkedList<>();
        queue.add("apple");
        queue.add("banana");
        queue.add("mango");
        System.out.println("Queue: "+ queue);
        while (!queue.isEmpty()) {
            System.out.println(queue.poll());
        }
    }
}