public class MinimumCommonValue {
    public int getCommon(int[] nums1, int[] nums2) {
        int val = -1;
        int i = 0, j = 0;
        while(i < nums1.length && j < nums2.length){
            if(nums1[i] == nums2[j]){
                val = nums1[i];
                break;
            }
            else if(nums1[i] < nums2[j]){
                i++;
            }else{
                j++;
            }
        }
        return val;
    }
}
