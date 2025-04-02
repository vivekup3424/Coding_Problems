import java.util.*;

class Solution {
    // Changed return type to Integer to handle null cases
    public Integer getSecondLargestElement(int[] arr) {
        if (arr == null || arr.length < 2) {
            return null;
        }
        
        Queue<Integer> minHeap = new PriorityQueue<>();
        
        for (int num : arr) {
            if (!minHeap.isEmpty() && minHeap.peek() == num) {
                continue;
            }
            minHeap.add(num);
            if (minHeap.size() > 2) {
                minHeap.poll();
            }
        }
        
        if (minHeap.size() < 2) {
            return null;
        }
        
        return minHeap.poll();
    }
}

public class TestSolution {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        // Test 1: Normal case
        int[] arr1 = {5, 10, 8, 12, 7};
        assert solution.getSecondLargestElement(arr1).equals(10) : "Test 1 failed";
        System.out.println("Test 1 passed: Normal case");
        
        // Test 2: With duplicates
        int[] arr2 = {5, 12, 12, 8, 5};
        assert solution.getSecondLargestElement(arr2).equals(8) : "Test 2 failed";
        System.out.println("Test 2 passed: With duplicates");
        
        // Test 3: All same elements
        int[] arr3 = {7, 7, 7, 7};
        assert solution.getSecondLargestElement(arr3) == null : "Test 3 failed";
        System.out.println("Test 3 passed: All same elements");
        
        // Test 4: Empty array
        int[] arr4 = {};
        assert solution.getSecondLargestElement(arr4) == null : "Test 4 failed";
        System.out.println("Test 4 passed: Empty array");
        
        // Test 5: Null array
        assert solution.getSecondLargestElement(null) == null : "Test 5 failed";
        System.out.println("Test 5 passed: Null array");
        
        // Test 6: Single element
        int[] arr6 = {42};
        assert solution.getSecondLargestElement(arr6) == null : "Test 6 failed";
        System.out.println("Test 6 passed: Single element");
        
        // Test 7: Two elements
        int[] arr7 = {3, 9};
        assert solution.getSecondLargestElement(arr7).equals(3) : "Test 7 failed";
        System.out.println("Test 7 passed: Two elements");
        
        // Test 8: Negative numbers
        int[] arr8 = {-5, -2, -10, -7};
        assert solution.getSecondLargestElement(arr8).equals(-5) : "Test 8 failed";
        System.out.println("Test 8 passed: Negative numbers");
        
        // Test 9: Duplicate maximum
        int[] arr9 = {3, 9, 9, 5, 8};
        assert solution.getSecondLargestElement(arr9).equals(8) : "Test 9 failed";
        System.out.println("Test 9 passed: Duplicate maximum");
        
        System.out.println("All tests passed!");
    }
}