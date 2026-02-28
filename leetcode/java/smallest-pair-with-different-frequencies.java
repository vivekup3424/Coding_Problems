import java.util.*;

class Solution {
    public int[] findPair(int[] nums) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.merge(num, 1, Integer::sum);
        }

        List<Integer> sortedValues = new ArrayList<>(frequencyMap.keySet());
        Collections.sort(sortedValues);

        // Iterate x in sorted order; for each x, find smallest y > x with different freq
        for (int i = 0; i < sortedValues.size(); i++) {
            int x = sortedValues.get(i);
            for (int j = i + 1; j < sortedValues.size(); j++) {
                int y = sortedValues.get(j);
                if (!frequencyMap.get(x).equals(frequencyMap.get(y))) {
                    return new int[]{x, y};
                }
            }
        }

        return new int[]{-1, -1};
    }
}
