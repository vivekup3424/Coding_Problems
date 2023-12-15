/*You are given positive integers low, high, and k.

A number is beautiful if it meets both of the following conditions:

    The count of even digits in the number is equal to the count of odd digits.
    The number is divisible by k.
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        int count = 0;
        // Iterate through each number in the range [low, high]
        for (int i = low; i <= high; i++) {
            int even_count = 0, odd_count = 0;
            int num = i;
            // Count the number of even and odd digits in the number
            while (num > 0) {
                int digit = num % 10;
                if (digit % 2 == 0) {
                    even_count++;
                } else {
                    odd_count++;
                }
                num /= 10;
            }
            // If the number has an equal count of even and odd digits and is divisible by k, increment the count
            if (even_count == odd_count && i % k == 0) {
                count++;
            }
        }
        return count;
    }
};   

int main()
{
    
}