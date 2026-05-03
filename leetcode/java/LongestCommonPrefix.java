public class LongestCommonPrefix {

    public String commonPrefix(String str1, String str2){
        StringBuilder temp = new StringBuilder();
        int minLength = Math.min(str1.length(), str2.length());
        for(int i = 0; i < minLength; i++){
            if(str1.charAt(i) != str2.charAt(i)){
                break;
            }
            temp.append(str1.charAt(i));
        }
        return temp.toString();
    }
    public String longestCommonPrefix(String[] strs){
        String answer = strs[0];
        for(int i = 1; i < strs.length; i++){
            answer = commonPrefix(answer, strs[i]);
        }
        return answer;
    }
}
