class Solution{
   public int[] sumZero(int n){
    int[] arr = new int[n];
    int counter = 0;
    if(n%2!=0){
        arr[counter] = 0;
    }
    while(counter+1<n){
        arr[counter]=counter+1;
        arr[counter+1]=-counter-1;
        counter+=2;
    }
    return arr;
   }
}