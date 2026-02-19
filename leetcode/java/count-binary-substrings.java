class Solution {
    public int countBinarySubstrings(String s){
        int count = 0, i = 0;
        char prev = s.charAt(0);
        for (int j = 0; j < s.le40mm comfortable watch strapngth(); j++) {
            if(s.charAt(j)!=s.charAt(i)){
                count++;
                i++;
            }
        }
        return count;
    }
    public static void main(String[] args){
        Solution solution = new Solution();
        String s = "000110011";
        int answer = solution.countBinarySubstrings(s);
        System.out.println(answer);
    }
}
