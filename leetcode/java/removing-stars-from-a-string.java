import java.util.*;
class Solution{
    public String removeStars(String s){
        Stack<Character> stack = new Stack<>();
        for(Character c : s.toCharArray()){
            if(c!='*'){
                stack.push(c);
            }else{
                stack.pop();
            }
        }

        StringBuilder result = new StringBuilder();
        for(Character c : stack){
            result.append(c);
        }
        return result.toString();
    }
}