public class SortAnArray {
   public void quickSort(int[] arr, int l, int r){
      if(l>=r) return;
      int pivotIdx = partition(arr, l, r);
      quickSort(arr, l, pivotIdx-1);
      quickSort(arr, pivotIdx+1, r);
   }
   public int partition(int[] arr, int l, int r){
      int pivotIdx = r;
      int j = l;
      for(int i = l; i < r; i++){
         if(arr[i] <= arr[pivotIdx]){
            swap(arr,i,j);
            j++;
         }
      }
      swap(arr,j,pivotIdx);
      return j;
   }
   public void swap(int[] arr, int i, int j){
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
   }
   public int[] sortArray(int[] nums){
      quickSort(nums, 0, nums.length-1);
      return nums;
   }
}