import java.util.*;
class Solution{
    public void eraseOverlapIntervals(int[][] intervals){
        Arrays.sort(intervals, (a,b)->Integer.compare(a[1], b[1]));
        System.out.println(intervals);
    }
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        Solution A = new Solution();
        System.out.println("Print the length of the array");
        int length = scanner.nextInt();
        List<List<Integer>> numbers = new ArrayList<Integer>();
        for(int i = 0; i < length; i++){
            int tempOne = scanner.nextInt();
            int tempTwo = scanner.nextInt();
            var newArray = new ArrayList<Integer>();
            newArray.add(tempOne);
            newArray.add(tempTwo);
            numbers.add(newArray);
        }
        scanner.close();
    }
}