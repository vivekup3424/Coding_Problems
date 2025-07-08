public class IsSubsequence {
   public boolean isSubsequence(String s, String t) {
    //check if s is a sebsequence of t
    int sIndex = 0, tIndex = 0;
    while(sIndex < s.length() && tIndex < t.length()){
        if(s.charAt(sIndex) == t.charAt(tIndex)){
            sIndex++;
        }
        tIndex++;
    }
    return sIndex == s.length();
   }
}
