import java.util.*;
class BinaryNumberWithAlternatingBits{
    public boolean hasAlternatingBits(int n){
        List<Integer> bits = new ArrayList<>();
        while(n>0){
            bits.add(n&1);
            n>>=1;
        }
        System.out.println(bits);
        for(int i = 1;i < bits.size(); i++){
            if(bits.get(i)==bits.get(i-1))return false;
        }
        return true;
    }
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of testcases");
        int t = scanner.nextInt();
        BinaryNumberWithAlternatingBits demo = new BinaryNumberWithAlternatingBits();
        while(t>0){
            int n = scanner.nextInt();
            boolean response = demo.hasAlternatingBits(n);
            System.out.println(response);
            t--;
        }
        scanner.close();
    }
}