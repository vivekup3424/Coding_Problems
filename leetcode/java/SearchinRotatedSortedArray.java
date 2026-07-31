public class SearchinRotatedSortedArray {

   public int search(int[] nums, int target){
        int n = nums.length;
        int l = 0, r = n-1;
        while(l <= r){
            int mid = (l+r)/2;
            if(nums[mid] == target) return mid;
            else if(nums[l] <= nums[mid]){ //[l...mid] is sorted
                if(nums[l]<=target && target<=nums[mid]){
                    r = mid-1;
                }else{
                    l = mid+1;
                }
            }else{
                //[r...mid] is sorted
               return 0; 
            }
        }
        return -1;
   }
}