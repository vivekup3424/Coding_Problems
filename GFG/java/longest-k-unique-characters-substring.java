import java.util.HashMap;
import java.util.Map;

class Solution{
    public int longestKSubstr(String s, int k){
        int max_length = 0;
        Map<Character, Integer> characterFreqMap = new HashMap<>();
        int j = 0;
        for(int i = 0; i < s.length(); i++){
            Character c = s.charAt(i);
            characterFreqMap.put(c,characterFreqMap.getOrDefault(c,0)+1);
            while(characterFreqMap.size() > k && j < i){
                Character l = s.charAt(j);
                characterFreqMap.put(l, characterFreqMap.get(l)-1);
                if(characterFreqMap.get(l)==0) characterFreqMap.remove(l);
                j++;
            }
            max_length = Math.max(max_length, i - j + 1);
        }
        return max_length;
    }
}