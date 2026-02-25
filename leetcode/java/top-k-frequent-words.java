import java.util.*;

class Solution {
    public List<String> topKFrequent(String[] words, int k) {
        Map<String, Integer> freqMap = new HashMap<>();
        for (String word : words) {
            freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);
        }

        // Max-heap: higher frequency first, ties broken alphabetically
        PriorityQueue<String> maxHeap = new PriorityQueue<>(
            (a, b) -> freqMap.get(a).equals(freqMap.get(b))
                ? a.compareTo(b)
                : freqMap.get(b) - freqMap.get(a)
        );

        maxHeap.addAll(freqMap.keySet());

        List<String> result = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            result.add(maxHeap.poll());
        }
        return result;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();

        String[] words1 = {"i", "love", "leetcode", "i", "love", "coding"};
        System.out.println(sol.topKFrequent(words1, 2));  // ["i", "love"]

        String[] words2 = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
        System.out.println(sol.topKFrequent(words2, 4));  // ["the", "is", "sunny", "day"]
    }
}