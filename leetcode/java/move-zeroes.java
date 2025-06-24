import java.util.ArrayList;
import java.util.Arrays;

class Solution {
    public void moveZeroes(int[] nums) {
        ArrayList<Integer> temp = new ArrayList<Integer>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                temp.add(nums[i]);
            }
        }
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 0) {
                temp.add(nums[i]);
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            nums[i] = temp.get(i);
        }
        return;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Test cases
        int[][] testCases = {
                { 0, 1, 0, 3, 12 },
                { 0 },
                { 1, 2, 3 },
                { 0, 0, 1 },
                { 1, 0, 0, 2, 0, 3 },
                { 0, 0, 0, 0 },
                {}
        };

        int[][] expected = {
                { 0, 0, 1, 3, 12 },
                { 0 },
                { 1, 2, 3 },
                { 0, 0, 1 },
                { 0, 0, 0, 1, 2, 3 },
                { 0, 0, 0, 0 },
                {}
        };

        System.out.println("Testing moveZeroes function:");
        System.out.println("=".repeat(50));

        for (int i = 0; i < testCases.length; i++) {
            int[] nums = testCases[i].clone(); // Clone to preserve original
            int[] expectedResult = expected[i];

            System.out.printf("Test %d:\n", i + 1);
            System.out.println("Input:    " + Arrays.toString(testCases[i]));

            solution.moveZeroes(nums);

            System.out.println("Output:   " + Arrays.toString(nums));
            System.out.println("Expected: " + Arrays.toString(expectedResult));

            boolean passed = Arrays.equals(nums, expectedResult);
            System.out.println("Result:   " + (passed ? "✓ PASS" : "✗ FAIL"));
            System.out.println();
        }
    }
}