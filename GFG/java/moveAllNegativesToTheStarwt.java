import java.util.Arrays;

public class moveAllNegativesToTheStarwt {
    private void naiveApproach(int[] arr){
        //sort in ascending order
        Arrays.sort(arr); //I am just adding lambda, because I want to practice writing it
        return;
    }
    private void twoPointers(int[] arr){
        //I don't think the order of positives would be preserved
        int n = arr.length;
        int i = 0, j = 0;
        while(j < n){
            if(arr[j]<0){
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                i++;
            }
            j++;
        }
    }
}