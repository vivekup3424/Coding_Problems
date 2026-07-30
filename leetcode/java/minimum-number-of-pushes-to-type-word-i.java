/*
 * 3014. Minimum Number of Pushes to Type Word I
 * https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/
 *
 * You are given a string word containing distinct lowercase English
 * letters. Telephone keys with letters mapped to them can be used to
 * form strings using taps.
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
 *   Input:  word = "xycdefghij"
 *   Output: 12
 *   Explanation: "x","y","c","d","e","f","g","h" each get their own key
 *     (one push each), and "i","j" share a key as the second letter
 *     (two pushes each). Total cost is 1 * 8 + 2 * 2 = 12.
 *
 * Constraints:
 *   - 1 <= word.length <= 26
 *   - word consists of distinct lowercase English letters.
 */


//this solution is for when letters are distinct
class Solution {
    public int minimumPushes(String word) {
        int count = 0;
        int MOD = 8;
        for(int i = 0; i < word.length(); i++){
            count += 1 + (i / MOD);
        }
        return count;
    }
}
