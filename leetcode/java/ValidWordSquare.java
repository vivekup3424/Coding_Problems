/**
 * Determine if an array of strings forms a valid word square.
 *
 * A word square is a grid where the k-th row equals the k-th column for all valid k.
 * In other words, words[i][j] == words[j][i] for all i, j.
 *
 * Example:
 *   words = ["abcd", "bnrt", "crmy", "dtye"]
 *
 *   a b c d
 *   b n r t
 *   c r m y
 *   d t y e
 *
 *   Row 0 == Col 0: "abcd"
 *   Row 1 == Col 1: "bnrt"
 *   Row 2 == Col 2: "crmy"
 *   Row 3 == Col 3: "dtye"  =>  valid
 */
public class ValidWordSquare {
    public boolean isValidWordSquare(String[] words) {
        int n = words.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].length(); j++) {
                if (j >= n || words[j].length() <= i || words[i].charAt(j) != words[j].charAt(i)) {
                    return false;
                }
            }
        }
        return true;
    }
}