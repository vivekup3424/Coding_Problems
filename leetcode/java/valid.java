import java.util.*;
class Solution{
    public boolean isAnagram(String s, String t){
        HashMap<Byte,Integer> hash_s = new HashMap<Byte,Integer>();
        for(int i = 0; i < s.length(); i++){
            if(hash_s.containsKey(s.charAt(s))){
                hash_s.put(s.charAt(i), 1 + hash_s.get(s.charAt(i)));
            }else{
                hash_s.put(s.charAt(i), 1);
            }
        }
        HashMap<Byte, Integer> hash_t = new HashMap<Byte,Integer>();
        for(int i = 0;i < t.length(); i++){
            if(hash_t.containsKey(t.charAt(i))){
                hash_t.put(t.charAt(i), 1 + hash_t.get(t.charAt(i)));
            }else{
                hash_t.put(s., null)
            }
        }
    }
}