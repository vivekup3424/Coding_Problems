class Solution{
    void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    void sortArray(int[] arr){
        int n = arr.length;
        int i = 0, j = 0, k = n-1;
        while(j<k){
            if(arr[j]==0){
                swap(arr, i, j);
                i++;
                j++;
            }else if(arr[j]==2){
                swap(arr, j, k);
                k--;
            }else{
                j++;
            }
        }
    }
}