import java.util.Random;

public class QuickSort {
    public void quicksort(int[] arr, int l, int r){
        int idx = partition(arr, l, r);
        partition(arr, l, idx);
        partition(arr, idx+1, r);
    }
    public int partition(int[] arr, int l , int r){
        int pivotIdx = l + (int)((r - l + 1) * Math.random());
        int j = l;
        for(int i = l; i <= r; i++){
            if(arr[i]>arr[pivotIdx])continue;
            //swap element at j and i
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            j++;
        }
        int temp = arr[pivotIdx];
        arr[pivotIdx] = arr[j];
        arr[j] = temp;
        return j;
    }
}