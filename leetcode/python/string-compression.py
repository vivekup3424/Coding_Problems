"""
443. String Compression
https://leetcode.com/problems/string-compression/

Given an array of characters chars, compress it using the following
algorithm:

Begin with an empty string s. For each group of consecutive repeating
characters in chars:
    - If the group's length is 1, append the character to s.
    - Otherwise, append the character followed by the group's length.

The compressed string s should not be returned separately, but instead, be
stored in the input character array chars. Note that group lengths that are
10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the
array.

You must write an algorithm that uses only constant extra space.

Example 1:
    Input:  chars = ["a","a","b","b","c","c","c"]
    Output: 6, chars = ["a","2","b","2","c","3"]
    Explanation: The groups are "aa", "bb", and "ccc". This compresses to
    "a2b2c3".

Example 2:
    Input:  chars = ["a"]
    Output: 1, chars = ["a"]
    Explanation: The only group is "a", which remains uncompressed since it's
    a single character.

Example 3:
    Input:  chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
    Output: 4, chars = ["a","b","1","2"]
    Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to
    "ab12".

Constraints:
    - 1 <= chars.length <= 2000
    - chars[i] is a lowercase English letter, uppercase English letter,
      digit, or symbol.
"""
from typing import List
class Solution:
    def addStringInPlace(self, chars: List[str], c: str, f: int, starting_idx: int) -> int:
        chars[starting_idx] = c
        idx = starting_idx + 1
        if f > 1:
            for digit in str(f):
                chars[idx] = digit
                idx += 1
        return idx
    def compress(self, chars: List[str]) -> int:
        if len(chars) < 2:
            return len(chars) # early exit
        i, n, idx = 0, len(chars), 0
        while i < n:
            c = chars[i]
            f = 0
            while i < n and chars[i] == c:
                f += 1
                i += 1
            idx = self.addStringInPlace(chars, c, f, idx)
        del chars[idx:]
        return idx