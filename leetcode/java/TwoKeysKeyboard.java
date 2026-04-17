public class TwoKeysKeyboard {
    /**
     * There is only one character 'A' on the screen of a notepad. 
     * You can perform one of two operations on this notepad for each step:
     * 
     * Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
     * Paste: You can paste the characters which are copied last time.
     * 
     * Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.
     */

    private int recurse(int length, int buffer, int target){
        if(length == target) return 1;
        else if(length > target) return Integer.MAX_VALUE;
        else{
            if(buffer != 0){
                return Math.min(
                    recurse(length+buffer, buffer, target), 
                    recurse(length, length, target)
                );
            }
            else{
                return recurse(length, buffer, target);
            }
        }
    }
    public int minSteps(int n){
        return 5;
    }
}
