import java.util.*;

class MinOpsParityAlternating {

    public int[] minOperations(int[] nums) {
        int n = nums.length;
        if (n == 1) return new int[]{0, 0};

        // Pattern A: even at even indices, odd at odd indices
        // Pattern B: odd at even indices, even at odd indices
        int costA = 0;
        for (int i = 0; i < n; i++) {
            int expected = i % 2;                        // 0=even, 1=odd
            int actual = ((nums[i] % 2) + 2) % 2;       // handles negatives
            if (actual != expected) costA++;
        }
        int costB = n - costA;
        int minCost = Math.min(costA, costB);

        long bestRange = Long.MAX_VALUE;
        if (costA <= costB) bestRange = Math.min(bestRange, computeRange(nums, 0));
        if (costB <= costA) bestRange = Math.min(bestRange, computeRange(nums, 1));

        return new int[]{minCost, (int) bestRange};
    }

    // patternType 0: even at even indices; 1: odd at even indices
    private long computeRange(int[] nums, int patternType) {
        int n = nums.length;
        List<long[]> cands = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int expected = (i + patternType) % 2;
            int actual = ((nums[i] % 2) + 2) % 2;

            if (actual == expected) {
                cands.add(new long[]{nums[i], i});          // fixed
            } else {
                cands.add(new long[]{(long) nums[i] - 1, i}); // choice: v-1
                cands.add(new long[]{(long) nums[i] + 1, i}); // choice: v+1
            }
        }

        cands.sort((a, b) -> Long.compare(a[0], b[0]));

        // Sliding window: find smallest interval covering all n elements
        int[] cover = new int[n];
        int covered = 0, left = 0;
        long minRange = Long.MAX_VALUE;

        for (int right = 0; right < cands.size(); right++) {
            int idx = (int) cands.get(right)[1];
            if (cover[idx]++ == 0) covered++;

            while (covered == n) {
                minRange = Math.min(minRange, cands.get(right)[0] - cands.get(left)[0]);
                int li = (int) cands.get(left)[1];
                if (--cover[li] == 0) covered--;
                left++;
            }
        }
        return minRange;
    }

    public static void main(String[] args) {
        MinOpsParityAlternating sol = new MinOpsParityAlternating();

        // Example 1: [-2,-3,1,4] → [2, 6]
        System.out.println(Arrays.toString(sol.minOperations(new int[]{-2, -3, 1, 4})));

        // Example 2: [0,2,-2] → [1, 3]
        System.out.println(Arrays.toString(sol.minOperations(new int[]{0, 2, -2})));

        // Example 3: [7] → [0, 0]
        System.out.println(Arrays.toString(sol.minOperations(new int[]{7})));
    }
}
