import java.util.*;

public class ConfusingNumber {
    /**
     * A confusing number is a number that becomes a different number when rotated 180 degrees, with all digits remaining valid after rotation.

When we rotate individual digits by 180 degrees:

    0 stays 0
    1 stays 1
    6 becomes 9
    8 stays 8
    9 becomes 6
    2, 3, 4, 5, and 7 become invalid (cannot be rotated)

The rotation process works by rotating each digit individually and reading the result from right to left. For example, if we have 69:

    The 6 rotates to 9
    The 9 rotates to 6
    Reading from right to left gives us 96

Since 96 ≠ 69, this is a confusing number.
     */
    public boolean isConfusingNumber(int num){
        Map<Integer, Integer> mirror = new HashMap<>();
        mirror.put(0,0);
        mirror.put(1,1);
        mirror.put(6,9);
        mirror.put(9,6);
        Set<Integer> invalids = new HashSet<>();
        invalids.addAll(

        )

        List<Integer> flippedArr = new ArrayList<>();
        while(num > 0){
            flippedArr.add(num % 10);
            num /= 10;
        }
    }
}