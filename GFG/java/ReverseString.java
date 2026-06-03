import java.util.ArrayDeque;
import java.util.Deque;

public class ReverseString {

    static String reverse(String s) {
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray())
            stack.push(c);

        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty())
            sb.append(stack.pop());

        return sb.toString();
    }

    static void test(String input, String expected) {
        String result = reverse(input);
        String status = result.equals(expected) ? "PASS" : "FAIL";
        System.out.println(status + " | input: \"" + input + "\" | expected: \"" + expected + "\" | got: \"" + result + "\"");
    }

    public static void main(String[] args) {
        test("hello",   "olleh");
        test("abcde",   "edcba");
        test("a",       "a");
        test("",        "");
        test("madam",   "madam");  // palindrome
        test("12345",   "54321");
    }
}
