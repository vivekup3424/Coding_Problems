/*
 * 3016. Minimum Number of Pushes to Type Word II
 * https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/
 *
 * You are given a string word containing lowercase English letters.
 * Telephone keys with letters mapped to them can be used to form
 * strings using taps.
 *
 * In this problem, you have keys numbered 2 to 9, each mapped to exactly
 * 8 lowercase English letters that you can arrange thoughtfully to
 * minimize the total number of taps required to type the string word.
 * This means letters mapped to the same key can be reordered.
 *
 * You need to find the minimum number of taps to type the string word
 * given the mapping.
 *
 * Return the minimum number of taps.
 *
 * Example 1:
 *   Input:  word = "abcde"
 *   Output: 5
 *   Explanation: With one letter per key, each letter costs one tap,
 *     for a total of 5.
 *
 * Example 2:
 *   Input:  word = "xyzxyzxyzxyz"
 *   Output: 12
 *   Explanation: "x","y","z" each get their own key, so each of the 12
 *     occurrences costs one tap.
 *
 * Example 3:
 *   Input:  word = "aabbccddeeffgghhiiiiii"
 *   Output: 24
 *   Explanation: "a" through "g" and "i" each get their own key (one
 *     push per occurrence), and "h" shares a key as the second letter
 *     (two pushes per occurrence). Total cost is 1*2*7 + 1*6 + 2*2 = 24.
 *
 * Constraints:
 *   - 1 <= word.length <= 10^5
 *   - word consists of lowercase English letters.
 */

import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class Solution {
    public int minimumPushes(String word) {
        Map<Character, Integer> freq = new HashMap<>();
        for(int i = 0; i < word.length(); i++){
            Character c = word.charAt(i);
            freq.put(c,freq.getOrDefault(c, 0)+1);
        }
        PriorityQueue<Character> maxHeap = new PriorityQueue<>(
            (a,b) -> freq.get(b) - freq.get(a)
        );
        maxHeap.addAll(freq.keySet());
        int idx = 0;
        int ans = 0, MOD = 8; 
        while(maxHeap.size() > 0){
            Character val = maxHeap.poll();
            ans += ((idx / MOD) + 1) * freq.get(val);
            idx++;
        }
        return ans; 
    }
}
