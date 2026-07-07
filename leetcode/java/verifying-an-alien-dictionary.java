/*
 * 953. Verifying an Alien Dictionary
 * https://leetcode.com/problems/verifying-an-alien-dictionary/
 *
 * In an alien language, surprisingly they also use English lowercase
 * letters, but possibly in a different order. The order of the alphabet is
 * some permutation of lowercase letters.
 *
 * Given a sequence of words written in the alien language, and the order of
 * the alphabet, return true if and only if the given words are sorted
 * lexicographically in this alien language.
 *
 * Example 1:
 *   Input:  words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
 *   Output: true
 *   Explanation: As 'h' comes before 'l' in this language, then the
 *   sequence is sorted.
 *
 * Example 2:
 *   Input:  words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
 *   Output: false
 *   Explanation: As 'd' comes after 'l' in this language, then words[0] >
 *   words[1], hence the sequence is unsorted.
 *
 * Example 3:
 *   Input:  words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
 *   Output: false
 *   Explanation: The first three characters "app" match, and the second
 *   string is shorter (in size.) According to lexicographical rules
 *   "apple" > "app", because 'l' > '∅', where '∅' is defined as the
 *   smallest possible character in this language.
 *
 * Constraints:
 *   - 1 <= words.length <= 100
 *   - 1 <= words[i].length <= 20
 *   - order.length == 26
 *   - All characters in words[i] and order are English lowercase letters.
 */

import java.util.HashMap;
import java.util.Map;

class Solution {
    private boolean isSmaller(String word1, String word2, Map<Character, Integer> indexOfMap){
        for(int i = 0; i < Math.min(word1.length(),word2.length()); i++){
            int idx1 = indexOfMap.get(word1.charAt(i));
            int idx2 = indexOfMap.get(word2.charAt(i));
            if(idx1 < idx2) return true;
            else if(idx1 > idx2) return false;
        }
        if(word1.length() > word2.length()) return false;
        return true;
    }
    public boolean isAlienSorted(String[] words, String order) {
        Map<Character,Integer> indexOfMap = new HashMap<>();
        for(int i = 0; i < order.length(); i++){
            indexOfMap.put(order.charAt(i),i);
        }
        for(int i = 0; i < words.length - 1; i++){
            if(!isSmaller(words[i], words[i + 1], indexOfMap)) return false;
        }
        return true;
    }
}
