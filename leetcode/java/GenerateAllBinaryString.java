import java.util.*;
class GenerateAllBinaryString {
    private static void generateSubstring(int idx, int n, Deque<Character> temp, List<String> values){
        if(idx==n){
            values.add(temp.toString());
            return;
        }
        temp.addLast('0');
        generateSubstring(idx+1, n, temp, values);
        temp.pollLast();
        temp.addLast('1');
        generateSubstring(idx+1, n, temp, values);
        temp.pollLast();
    }
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        System.out.println("received n = "+n);
        Deque<Character> temp = new ArrayDeque<Character>();
        List<String> values = new ArrayList<>();
        generateSubstring(0,n,temp,values);
        System.out.println(values);
        scanner.close();
    }
}