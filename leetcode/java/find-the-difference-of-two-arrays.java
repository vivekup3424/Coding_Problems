import java.util.*;
class Solution{
    public List<List<Integer>> findDifference(int[] nums1 ,int[] nums2){
        Set<Integer> set1 = new HashSet<>();
        for(int num : nums1) set1.add(num);

        Set<Integer> set2 = new HashSet<>();
        for(int num : nums2) set2.add(num);

        set1.removeAll(set2);
        set2.removeAll(set1);

        return Arrays.asList(new ArrayList<>(set1), new ArrayList<>(set2));
        //you know where you are dvs
    }
}