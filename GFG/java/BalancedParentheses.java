import java.util.ArrayDeque;
import java.util.Deque;

public class BalancedParentheses {

    static boolean isBalanced(String s) {
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            } else {
                if (stack.isEmpty()) return false;

                char top = stack.pop();
                if (c == ')' && top != '(') return false;
                if (c == '}' && top != '{') return false;
                if (c == ']' && top != '[') return false;
            }
        }

        return stack.isEmpty();
    }

    static void test(String input, boolean expected) {
        boolean result = isBalanced(input);
        String status = result == expected ? "PASS" : "FAIL";
        System.out.println(status + " | input: \"" + input + "\" | expected: " + expected + " | got: " + result);
    }

    public static void main(String[] args) {
        test("({[]})",  true);   // properly nested
        test("([)]",    false);  // wrong order
        test("{[",      false);  // unclosed brackets
        test("",        true);   // empty string
        test("()",      true);   // single pair
        test("(((",     false);  // only opening
        test(")))",     false);  // only closing
        test("{[()]}",  true);   // deeply nested
        test("(]",      false);  // mismatched types
        test("()[]{}", true);    // multiple pairs in sequence
    }
}
