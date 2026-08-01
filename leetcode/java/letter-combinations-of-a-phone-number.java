/*
 * 17. Letter Combinations of a Phone Number
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer
 * in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons) is
 * given below. Note that 1 does not map to any letters.
 *
 * Example 1:
 *   Input:  digits = "23"
 *   Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example 2:
 *   Input:  digits = ""
 *   Output: []
 *
 * Example 3:
 *   Input:  digits = "2"
 *   Output: ["a","b","c"]
 *
 * Constraints:
 *   - 0 <= digits.length <= 4
 *   - digits[i] is a digit in the range ['2', '9'].
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    Map<Character, String> characterMap;

    void recurse(String digits, int idx, StringBuffer temp, List<String> answer){
        if(idx == digits.length()){
            answer.add(temp.toString());
            return;
        }
        String letters = characterMap.get(digits.charAt(idx));
        for(int i = 0; i < letters.length(); i++){
            temp.append(letters.charAt(i));
            recurse(digits, idx+1, temp, answer);
            temp.deleteCharAt(temp.length()-1);
        }
    }
    public List<String> letterCombinations(String digits) {
        characterMap = new HashMap<>();
        characterMap.put('2', "abc");
        characterMap.put('3', "def");
        characterMap.put('4', "ghi");
        characterMap.put('5', "jkl");
        characterMap.put('6', "mno");
        characterMap.put('7', "pqrs");
        characterMap.put('8', "tuv");
        characterMap.put('9', "wxyz");

        List<String> result = new ArrayList<>();
        StringBuffer temp = new StringBuffer();
        if(digits.length()==0) return result;
        recurse(digits, 0, temp, result);
        return result;
    }
}
