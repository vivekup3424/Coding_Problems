import java.util.*;

public class NextPermutation {
    private boolean isIncreasing(int[] nums){
        for(int i = 1; i < nums.length; i++){
            if(nums[i]<nums[i-1]){
                return false;
            }
        }
        return true;
    }
    public void nextPermutation(int[] nums) {
        //early detection
        if(isIncreasing(nums)){
            int i = 0, j = nums.length-1;
            while(i<j){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
            return;
        }
        for (int i = nums.length - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] < nums[i]) {
                    int temp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = temp;
                    System.out.printf(" j = %d, i = %d\n", i, j);
                    if (j + 1 < i - 1) {
                        Arrays.sort(nums, j + 1, i);
                    }
                    return;
                }
            }
        }
    }
}
