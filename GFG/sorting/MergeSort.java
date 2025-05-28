import java.util.ArrayList;
import java.util.Scanner;

public class MergeSort {
    public static void merge(ArrayList<Integer> arr, Integer l, Integer mid, Integer r){
        ArrayList<Integer> temp1 = new ArrayList<Integer>();
        ArrayList<Integer> temp2 = new ArrayList<Integer>();

        for(Integer i = l; i <= mid; i++){
            temp1.add(arr.get(i));
        }
        for(Integer i = mid+1; i <= r; i++){
            temp2.add(arr.get(i));
        }
        int i = 0, j = 0, k = l;
        while(i<temp1.size() && j < temp2.size()){
            if(temp1.get(i) <= temp2.get(j)){
                arr.set(k,temp1.get(i));
                i++;
            }else{
                arr.set(k,temp2.get(j));
                j++;
            }
            k++;
        }
        while(i<temp1.size()){
            arr.set(k,temp1.get(i));
            i++;
            k++;
        }
        while(j<temp2.size()){
            arr.set(k, temp2.get(j));
            j++;
            k++;
        }
    }

    public ArrayList<Integer> mergesort(ArrayList<Integer> arr, Integer l, Integer r) {
        if (l < r) {
            var mid = (l + r) / 2;
            mergesort(arr, l, mid);
            mergesort(arr, mid + 1, r);
            merge(arr, l, mid, r);
        }
        return arr;
    }

    // Method to display array
    public static void printArray(ArrayList<Integer> arr) {
        for (int i = 0; i < arr.size(); i++) {
            System.out.print(arr.get(i) + " ");
        }
        System.out.println();
    }

    // Main method with user input
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MergeSort ms = new MergeSort();
        
        System.out.print("Enter the number of elements: ");
        int n = scanner.nextInt();
        
        ArrayList<Integer> arr = new ArrayList<>();
        
        System.out.println("Enter " + n + " integers:");
        for (int i = 0; i < n; i++) {
            int element = scanner.nextInt();
            arr.add(element);
        }
        
        System.out.println("\nOriginal array:");
        printArray(arr);
        
        // Sort the array
        ms.mergesort(arr, 0, arr.size() - 1);
        
        System.out.println("\nSorted array:");
        printArray(arr);
        
        scanner.close();
    }
}
