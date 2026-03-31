class BubbleSort{
    void sort(int[] arr){
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++){
                if(arr[j-1]>arr[j]){
                    int temp = arr[j-1];
                    arr[j-1] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
}