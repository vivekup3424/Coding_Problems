import java.util.*;
class Solution{
    public String reverseWords(String s){
        List<String> words = new ArrayList<>();
        StringBuilder temp = new StringBuilder();
        int i = 0;
        while (i < s.length()) {
            if(s.charAt(i)==' '){
                words.add(temp.toString());
                temp = new StringBuilder();
                while(i<s.length() && s.charAt(i)==' '){
                    i++;
                }
            }else{
                temp.append(s.charAt(i));
                i++;
            }
        }
        if(!temp.isEmpty()){
            words.add(temp.toString());
        }
        //reverse the words
        int l = 0, r = words.size()-1;
        while (l<r) {
            var temp_word = words.get(l);
            words.set(l, words.get(r));
            words.set(r, temp_word);
        }
        StringBuilder answer = new StringBuilder();
        for(String word: words){
            answer.append(word);
            answer.append(" ");
        }
        return answer.toString().trim();
    }
}