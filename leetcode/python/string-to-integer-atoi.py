"""
8. String to Integer (atoi)
https://leetcode.com/problems/string-to-integer-atoi/

Implement the myAtoi(string s) function, which converts a string to a 32-bit
signed integer.

The algorithm for myAtoi(string s) is as follows:
    1. Whitespace: Ignore any leading whitespace (" ").
    2. Signedness: Determine the sign by checking if the next character is '-'
       or '+', assuming positivity if neither present.
    3. Conversion: Read the integer by skipping leading zeros until a
       non-digit character is encountered or the end of the string is
       reached. If no digits were read, then the result is 0.
    4. Rounding: If the integer is out of the 32-bit signed integer range
       [-2^31, 2^31 - 1], then round the integer to remain in the range.
       Specifically, integers less than -2^31 should be rounded to -2^31, and
       integers greater than 2^31 - 1 should be rounded to 2^31 - 1.

Return the integer as the final result.

Example 1:
    Input:  s = "42"
    Output: 42

Example 2:
    Input:  s = " -042"
    Output: -42
    Explanation: Leading whitespace is ignored, the sign is read, and leading
    zeros are skipped.

Example 3:
    Input:  s = "1337c0d3"
    Output: 1337
    Explanation: Reading stops at 'c' since it is not a digit.

Example 4:
    Input:  s = "0-1"
    Output: 0
    Explanation: Reading stops at '-' since it is not a digit.

Example 5:
    Input:  s = "words and 987"
    Output: 0
    Explanation: Reading stops at the first non-whitespace character 'w'.

Constraints:
    - 0 <= s.length <= 200
    - s consists of English letters (lower-case and upper-case), digits
      (0-9), ' ', '+', '-', and '.'.
"""
class Solution:
    def myAtoi(self, s: str) -> int:
        pass
