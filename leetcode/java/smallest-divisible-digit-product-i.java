/*
 * 3345. Smallest Divisible Digit Product I
 * https://leetcode.com/problems/smallest-divisible-digit-product-i/
 *
 * You are given two integers n and t. Return the smallest number greater
 * than or equal to n such that the product of its digits is divisible
 * by t.
 *
 * Example 1:
 *   Input:  n = 10, t = 2
 *   Output: 10
 *   Explanation: The digit product of 10 is 0. 0 is divisible by 2, hence
 *                10 is the answer.
 *
 * Example 2:
 *   Input:  n = 15, t = 3
 *   Output: 16
 *   Explanation: The digit product of 16 is 6. 6 is divisible by 3, hence
 *                16 is the answer.
 *
 * Constraints:
 *   - 1 <= n <= 100
 *   - 1 <= t <= 10
 */
class Solution {
    private int productDigits(int n){
        int product = 1;
        while(n > 0){
            product *= (n%10);
            n /= 10;
        }
        return product;
    }
    public int smallestNumber(int n, int t) {
        int num = n;
        while(true){
            if(productDigits(num) % t == 0)return num;
            num++;
        }
    }
}
