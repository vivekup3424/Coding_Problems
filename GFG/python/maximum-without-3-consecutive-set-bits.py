"""
Maximum Without 3 Consecutive Set Bits

Given a non-negative integer n, you can only change a set bit (1) to an unset
bit (0). Find the maximum possible value of n such that its binary
representation does not contain three consecutive set bits (111) after
performing zero or more allowed operations.

Example 1:
    Input:  n = 2
    Output: 2
    Explanation: The binary representation of 2 is 10, which does not contain
    three consecutive set bits. Therefore, no change is required.

Example 2:
    Input:  n = 7
    Output: 6
    Explanation: The binary representation of 7 is 111, which contains three
    consecutive set bits. Changing the rightmost set bit to 0 gives:
    111 -> 110. Thus, the maximum possible value is 6.

Constraints:
    - 0 <= n <= 10^9
"""
class Solution:
    def maxValue(self, n: int) -> int:
        ans = []
        
        """code here"""

