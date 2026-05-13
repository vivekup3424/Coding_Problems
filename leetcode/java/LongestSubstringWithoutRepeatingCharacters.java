import java.util.HashSet;
import java.util.Set;

public class LongestSubstringWithoutRepeatingCharacters {

    public int lengthOfLongestSubstring(String s){
        Set<Character> st = new HashSet<>();
        int n = s.length();
        int l = 0, r = 0;
        int maxLength = 0;
        while (r < n) {
            while(st.contains(s.charAt(r))){
                st.remove(s.charAt(l));
                l++;
            }
            st.add(s.charAt(r));
            maxLength = Integer.max(maxLength, r - l +1);
            r++;
        }
        return maxLength;
    }
}