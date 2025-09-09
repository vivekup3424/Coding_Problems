import java.util.*;
class Solution {
    void backtrack(int[] nums, int idx, ArrayList<Integer> elements, ArrayList<ArrayList<Integer>> st){
        if(idx==nums.length){
            st.add(new ArrayList<>(elements));
            return;
        }
        elements.add(nums[idx]);
        backtrack(nums, idx+1, elements, st);
        elements.remove(elements.size()-1);
        backtrack(nums, idx, elements, st);
    }
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        List<List<Integer>> answer = new ArrayList<>();
        Arrays.sort(nums);
        backtrack(nums, 0, [], null);
        return answer;
    }
}