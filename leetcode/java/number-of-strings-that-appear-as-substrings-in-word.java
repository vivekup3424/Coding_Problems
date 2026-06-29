import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Given an array of strings patterns and a string word, 
 * return the number of strings in patterns that exist as a substring in word.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * Solution
 */
class Solution{
    public int numOfStrings(String[] patterns, String word){
        Set<String> substrings = new HashSet<>();
        for (int i = 0; i < word.length(); i++) {
           for(int j = i; j < word.length(); j++){
            String substr = word.substring(i, j+1);
            substrings.add(substr);
           }
        }
        int count = 0;
        for(String pattern : patterns){
            if(substrings.contains(pattern))count+=1;
        }
        return count;
    }
}