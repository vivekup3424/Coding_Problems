import java.util.*;
/**
 * You are given two integer arrays nums1 and nums2, where nums2 is an anagram of nums1. 
 * This means nums2 contains exactly the same elements as nums1, 
 * but potentially in a different order. Both arrays may contain duplicate values.

Your task is to create an index mapping array called mapping that shows 
where each element from nums1 appears in nums2. Specifically, mapping[i] = j 
means that the element at position i in nums1 can be found at position j in nums2.
 */

public class FindAnagramMappings {
    public int[] anagramMappings(int[] nums1, int[] nums2){
        Map<Integer, Set<Integer>> valToIndices = new HashMap<>();
        for(int i = 0; i < nums2.length; i++){
            valToIndices.computeIfAbsent(nums2[i], k -> new HashSet<>()).add(i);
        }
        int[] result = new int[nums1.length];
        for(int i = 0; i < nums1.length; i++){
            result[i] = valToIndices.get(nums1[i]).iterator().next();
            valToIndices.get(nums1[i]).remove(result[i]);
        }
        return result;
    }
}