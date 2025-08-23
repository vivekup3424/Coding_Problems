public class NextPermutation {
    public void nextPermutation(int[] nums) {
        int pivot_idx = -1;
        for(int i = nums.length-1; i > 0; i++){
            if(nums[i-1]<nums[i]){
                pivot_idx = i;
                break;
            }
        } 
        //reverse the array 
        int l = pivot_idx, r = nums.length-1;
        while(l<r){
            int temp = nums[l];
            nums[l] = nums[r];
            nums[r] = temp;
            l++;
            r--;
        }
        if(pivot_idx!=-1){
            for(int i = pivot_idx; i < nums.length; i++){
                if(nums[i]>nums[pivot_idx-1])
            }
        }
        return ;
    }
}
