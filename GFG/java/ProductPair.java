public class ProductPair {
    public boolean isProduct(int[] arr, long target){
        Arrays.sort(arr);
        int i = 0, j = arr.length-1;
        while(i<j){
            long product = (long) arr[i] * (long) arr[j];
            if(product == target) return true;
            else if(product < target) i++;
            else j--;
        }
        return false;
    }
}
