import java.util.ArrayList;
import java.util.List;

public class ConcantenationOfArray {
    public int[] getConcantenation(int[] nums){
        List<Integer> ans = new ArrayList<>();
        for(int i = 0; i < nums.length; i++){
            ans.add(nums[i]);
        }
        for(int i = 0; i < nums.length; i++){
            ans.add(nums[i]);
        }
        return ans.toArray(Integer);
    }
}
