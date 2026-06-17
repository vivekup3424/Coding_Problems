class Solution {
    public int appendCharacters(String s, String t) {
        if(t.length() == 0) return 0;
        int j = 0; //t
        for(int i = 0; i < s.length() && j < t.length(); i++){
            if(s.charAt(i) == t.charAt(j)) j++;
        }
        return t.length() - j;
    }
}