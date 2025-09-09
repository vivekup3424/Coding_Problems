package GFG.recursion;
import java.util.ArrayList;

public class SubsetSums {
    static void findSubSums(int arr[], int idx, int sum, ArrayList<Integer> result){
        if(idx == -1){
            result.add(sum);
            return;
        }
        findSubSums(arr, idx - 1, sum + arr[idx], result);
        findSubSums(arr, idx - 1, sum, result);
    }
    public static void main(String[] args) {
        int arr[] = {3, 1, 2};
        ArrayList<Integer> result = new ArrayList<>();
        findSubSums(arr, arr.length - 1, 0, result);
        System.out.println(result);
    }
}
