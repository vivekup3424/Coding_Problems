/**
 * given an array containing n balls of 3 colors, red, green, blue
 * the balls are in random order eg, RBGGRGBG
 * we need to sort them so that the new order is
 * such that Red one's appear first, then all greens, and then all blues
 * for this example, new order would be RRGGGBB
 * since the array is an integer array hence
 * R = 0
 * G = 1
 * B = 2
 */
public class SortColors {
    public void sort(int[] nums){
        int n = nums.length;
        int i = 0, j = 0, k = n-1;
        while(j <= k){
            if(nums[j]==0){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                i++;
                j++;
            }
            else if(nums[j]==1){
                j++;
            }
            else{
                int temp = nums[k];
                nums[k] = nums[j];
                nums[j] = temp;
                k--;
            }
        }
    }
}
