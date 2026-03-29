class Solution{
    void rotateByRight(int[] arr, int k){
        int n = arr.length;
        k = k % n;
        if (k == 0) return;
        int[] temp = new int[k];
        for(int i = 0; i < k; i++){
            temp[i] = arr[n-k+i]; //moving the last k elements
        }
        for(int j = n-k-1; j >= 0; j--){
            arr[j+k] = arr[j];
        }
        for (int i = 0; i < temp.length; i++) {
            arr[i] = temp[i];
        }
    }
    void rotateByLeft(int[] arr, int k){
        int n = arr.length;
        k = k % n;
        if (k==0) return;
        int[] temp = new int[k];
        for (int i = 0; i < k; i++) {
           temp[i] = arr[i]; //moving the first k elements to array
        }
        //move the remaining elements to front;
        for(int i = k; i < n; i++){
            arr[i-k] = arr[i];
        }
        for(int i = 0; i < k; i++){
            arr[n-k+i] = temp[i];
        }
    }
}