import java.util.*;
class Solution{
    public String reverseVowels(String s){
        char[] word = s.toCharArray();
        String vowels = "aeiouAEIOU";
        int l = 0, r = s.length()-1;
        while (l<r) {
            while(l<r && vowels.indexOf(word[l])==-1){
                l++;
            }
            while(r>l && vowels.indexOf(word[r])==-1){
                r--;
            }
            char temp = word[l];
            word[l] = word[r];
            word
        }
    }
}