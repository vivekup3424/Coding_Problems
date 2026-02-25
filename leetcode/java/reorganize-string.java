import java.util.*;

class Solution{
    public String reorganizeString(String s){
        //maxHeap of frequencies
        //then place the element at max freq alternatively,
        //if at any time the adjacent characters are same, then return ""
        //else return answer for going over all the characters
        Map<Character,Integer> freqMap = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            Character c = s.charAt(i);
            freqMap.put(c, freqMap.getOrDefault(c, 0) + 1);
        }

        // Max-heap: higher frequency character comes first
        PriorityQueue<Character> maxHeap = new PriorityQueue<>(
            (a, b) -> freqMap.get(b) - freqMap.get(a)
        );
        maxHeap.addAll(freqMap.keySet());

        StringBuilder sb = new StringBuilder();
        while (maxHeap.size() >= 2) {
            // Pick top two most frequent characters
            char first = maxHeap.poll();
            char second = maxHeap.poll();

            sb.append(first);
            sb.append(second);

            // Decrement frequencies and re-add if still remaining
            freqMap.put(first, freqMap.get(first) - 1);
            freqMap.put(second, freqMap.get(second) - 1);

            if (freqMap.get(first) > 0) maxHeap.offer(first);
            if (freqMap.get(second) > 0) maxHeap.offer(second);
        }

        // One character may remain
        if (!maxHeap.isEmpty()) {
            char last = maxHeap.poll();
            if (freqMap.get(last) > 1) return ""; // can't place without adjacency
            sb.append(last);
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println(sol.reorganizeString("aab"));   // "aba"
        System.out.println(sol.reorganizeString("aaab"));  // ""
        System.out.println(sol.reorganizeString("vvvlo")); // "vlvov" or similar
    }
}