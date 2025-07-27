import java.util.Scanner;

class Solution {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] arr = new int[n];
        for(int i = 0; i < n; i++){
            arr[i] = scanner.nextInt();
        }
        Solution A = new Solution();
        System.out.println(A.countHillValley(arr));
        scanner.close();
    }
    private boolean isPeak(int left, int peak, int right){
        return (left < peak && peak > right);
    }
    private boolean isValley(int left, int bottom, int right){
        return (left > bottom && bottom < right);
    }
    public int countHillValley(int[] nums) {
        if (nums.length == 1) {
            return 1;
        }
        int count = 0;
        int prev_element = 0, current_element = 1;
        while (current_element < nums.length - 1) {
            boolean isPeak = isPeak(nums[prev_element], nums[current_element], nums[current_element+1]);
            boolean isValley = isValley(nums[prev_element], nums[current_element], nums[current_element+1]);
            if(isPeak || isValley){
                count++;
            }
            current_element++;
            if(nums[current_element] != nums[current_element-1]){
                prev_element=current_element-1;
            }
        }
        return count;
    }
}