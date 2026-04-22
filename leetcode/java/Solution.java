public class Solution {
    public static void main(String[] args){
        int[] original_arr = {1,2,3,4,5};
        System.out.println("Original Array = ");
        System.out.println(original_arr);
        int[] copy_arr = original_arr;
        copy_arr[4] = 100;
        System.out.println("Copied Array = ");
        System.out.println(copy_arr);
        System.out.println("Original Array = ");
        System.out.println(original_arr);
    }
}
