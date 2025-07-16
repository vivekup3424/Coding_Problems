import java.util.*;
class Solution {
    public String removeStars(String s) {
        Deque<Character> stack = new ArrayDeque<Character>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '*') {
                stack.pop(); // since this operation is always possible(according to question)
            } else {
                stack.push(c);
            }
        }
        StringBuilder answer = new StringBuilder();
        while (stack.isEmpty() == false) {
            answer.append(stack.pop());
        }
        return answer.reverse().toString();
    }
}