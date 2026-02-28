import java.util.*;

class MergeCloseCharacters {
    public String mergeCloseCharacters(String s, int k) {
        List<Character> chars = new ArrayList<>();
        for (char c : s.toCharArray()) chars.add(c);

        boolean found = true;
        while (found) {
            found = false;
            outer:
            for (int i = 0; i < chars.size(); i++) {
                int limit = Math.min(i + k, chars.size() - 1);
                for (int j = i + 1; j <= limit; j++) {
                    if (chars.get(i).equals(chars.get(j))) {
                        chars.remove(j);  // right merges into left (right is deleted)
                        found = true;
                        break outer;      // restart from beginning after every merge
                    }
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (char c : chars) sb.append(c);
        return sb.toString();
    }

    public static void main(String[] args) {
        MergeCloseCharacters sol = new MergeCloseCharacters();

        // Test 1: basic pair within k
        System.out.println(sol.mergeCloseCharacters("aab", 1));    // "ab"

        // Test 2: pair at exact distance k
        System.out.println(sol.mergeCloseCharacters("aba", 2));    // "ab"

        // Test 3: pair too far apart
        System.out.println(sol.mergeCloseCharacters("aba", 1));    // "aba"

        // Test 4: cascading merges
        System.out.println(sol.mergeCloseCharacters("abacaba", 2)); // "abcab"

        // Test 5: all same chars
        System.out.println(sol.mergeCloseCharacters("aaaa", 1));   // "a"
    }
}
