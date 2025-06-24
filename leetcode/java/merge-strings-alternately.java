class Solution{
    public String mergeAlternately(String word1, String word2){
        var result = new StringBuilder();
        Integer i = 0;
        while (i<word1.length() && i < word2.length()) {
            result.append(word1.charAt(i));
            result.append(word2.charAt(i));
            i+=1;
        }
        if(i!=word1.length()){
            result.append(word1.substring(i));
        }
        if(i!=word2.length()){
            result.append(word2.substring(i));
        }
        return result.toString();
    }
}