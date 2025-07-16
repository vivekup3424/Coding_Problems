import java.util.*;

class Solution {
    public List<List<Integer>> findDifference(int[] nums1, int[] nums2) {
        List<List<Integer>> answer = new ArrayList<>();
        Set<Integer> nums1Set = new HashSet<>();
        Set<Integer> nums2Set = new HashSet<>();
        for (int i = 0; i < nums1.length; i++) {
            nums1Set.add(nums1[i]);
        }
        for (int i = 0; i < nums2.length; i++) {
            nums2Set.add(nums2[i]);
        }
        List<Integer> answerOne = new ArrayList<>();
        for (int i = 0; i < nums1.length; i++) {
            if(nums2Set.contains(nums1[i])==false){
                answerOne.add(nums1[i]);
            }
        }
        List<Integer> answerTwo = new ArrayList<>();
        for (int i = 0; i < nums2.length; i++) {
            if(nums1Set.contains(nums2[i])==false){
                answerTwo.add(nums2[i]);
            }
        }
        answer.add(answerOne);
        answer.add(answerTwo);
        return answer;
    }
}