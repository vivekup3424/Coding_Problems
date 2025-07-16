import java.util.*;
class Solution{
    public int maxVowels(String s, int k){
        Set<Character> vowels = new HashSet<>();
        vowels.addAll(Arrays.asList('a', 'e', 'i', 'o','u'));
        int current_count = 0;
        for(int i = 0; i < k; i++){
            if(vowels.contains(s.charAt(i))){
                current_count+=1;
            }
        }
        int max_so_far = current_count;
        for(int i = k; i< s.length(); i++){
            if(vowels.contains(s.charAt(i))){
                current_count+=1;
            }
            if(vowels.contains(s.charAt(i-k))){
                current_count-=1;
            }
            if(current_count>max_so_far){
                max_so_far = current_count;
            }
        }
        return max_so_far;
    }
}