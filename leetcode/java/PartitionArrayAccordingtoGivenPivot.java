import java.util.ArrayList;
import java.util.List;

public class PartitionArrayAccordingtoGivenPivot {

    public int[] pivotArray(int[] nums, int pivot){
        int n = nums.length;
        int[] answer = new int[n];
        for(int j = 0 ; j < n; j++) answer[j] = pivot;
        int j = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] < pivot){
                answer[j++] = nums[i];
            }
        }
        j = n-1;
        for(int i = n-1; i >= 0; i--){
            if(nums[i]>pivot){
                answer[j--] = nums[i];
            }
        }
        return answer;
    }
}