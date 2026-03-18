/**
 * Simple standalone tests for Solution.countSubstrings(String s, int x).
 * Run: javac Solution.java SolutionTest.java && java SolutionTest
 */
class SolutionTest {
    static int passed = 0, failed = 0;

    static void assertEqual(String label, int expected, int actual) {
        if (expected == actual) {
            System.out.println("PASS: " + label);
            passed++;
        } else {
            System.out.println("FAIL: " + label + " — expected " + expected + ", got " + actual);
            failed++;
        }
    }

    static void assertTrue(String label, boolean condition) {
        if (condition) {
            System.out.println("PASS: " + label);
            passed++;
        } else {
            System.out.println("FAIL: " + label);
            failed++;
        }
    }

    public static void main(String[] args) {
        // Basic case: "1234", x=1 — substrings: 1(no),2(yes),3(yes),4(yes),12(yes),23(yes),34(yes),123(yes),234(yes),1234(yes)
        // Substrings > 1: 2,3,4,12,23,34,123,234,1234 = 9
        assertEqual("basic case", 9, Solution.countSubstrings("1234", 1));

        // All substrings start with 0 or are <= x
        assertEqual("all zeros", 0, Solution.countSubstrings("000", 0));

        // Single digit equal to x — not greater, so 0
        assertEqual("single digit equal x", 0, Solution.countSubstrings("5", 5));

        // Single digit greater than x
        assertEqual("single digit greater", 1, Solution.countSubstrings("5", 4));

        // Leading zero skipped: "021" — valid starts: '2'->2,21; '1'->1. x=0 => all 3 count
        assertEqual("leading zero skipped", 3, Solution.countSubstrings("021", 0));

        // Mixed: "103", x=2 — valid substrings (no leading 0):
        // start=0: 1(no),10(yes),103(yes)
        // start=1: skip (s[1]='0')
        // start=2: 3(yes)
        // => 3
        assertEqual("mixed with internal zero", 3, Solution.countSubstrings("103", 2));

        // x=0, all non-zero-starting substrings count
        // "12": 1,2,12 => 3
        assertEqual("x=0", 3, Solution.countSubstrings("12", 0));

        // Large number won't overflow (uses long internally)
        // "99999999999" > Integer.MAX_VALUE, just check no exception and count > 0
        int result = Solution.countSubstrings("99999999999", 1000000000);
        assertTrue("large number no overflow", result > 0);

        System.out.println("\n" + passed + " passed, " + failed + " failed.");
    }
}