import java.util.*;

public class CheckAdjacentDigitDifferences {

    public boolean isAdjacentDiffAtMostTwo(String s){
        int n = s.length();
        for (int i = 1; i < n; i++) {
            int a = s.charAt(i) - '1';
            int b = s.charAt(i-1) - '1';
            if(Math.abs(a-b) > 2) return false;
        }
        return true;
    }
}