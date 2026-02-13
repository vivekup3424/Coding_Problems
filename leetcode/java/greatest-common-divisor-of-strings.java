class Solution {
    private boolean canFormCompleteString(String gcd, String str1){
        int len_gcd = gcd.length(), len_str = str1.length();
        if(len_str % len_gcd != 0){
            return false;
        }
        String ans = gcd.repeat(len_str/len_gcd);
        return ans.equals(str1);
    }
    public String gcdOfStrings(String str1, String str2) {
        StringBuilder prefix = new StringBuilder();
        String gcd = "";
        for (int i = 0; i < Math.min(str1.length(), str2.length()) && (str1.charAt(i) == str2.charAt(i)); i++) {
            prefix.append(str1.charAt(i));
            boolean canFormStr1 = canFormCompleteString(prefix.toString(), str1);
            boolean canFormStr2 = canFormCompleteString(prefix.toString(), str2);
            if(canFormStr1 && canFormStr2){
                gcd = prefix.toString();
            }
        }
        return gcd;
    }
}