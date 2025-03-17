import java.util.*;;
class Solution {
    public boolean divideArray(int[] nums) {
        Map<Integer,Integer> freq = new HashMap<>();
        for(int num : nums){
        freq.put(num, freq.getOrDefault(num, 0)+1);
        }
        for(int val : freq.values()){
            if(val % 2 == 1){
                return false;
            }
        }
        return true;
    }
}