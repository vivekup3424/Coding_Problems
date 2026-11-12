"""
4106. Find Mismatched Segments Between Two Strings
https://leetcode.com/problems/find-mismatched-segments-between-two-strings/

You are given two strings s1 and s2 of the same length.

A mismatched segment is a maximal contiguous range of indices where the
characters of s1 and s2 differ at every index.

Return a 2D array containing [sub1, sub2] for each mismatched segment, where
sub1 and sub2 are the corresponding substrings from s1 and s2, respectively.
Return the segments in increasing order of their starting indices. If there
are no mismatched segments, return an empty array.

Example 1:
    Input:  s1 = "earth", s2 = "empty"
    Output: [["ar","mp"],["h","y"]]
    Explanation: The characters at indices 1 and 2 differ, forming the
    mismatched segment ["ar","mp"]. The characters at index 4 differ, forming
    the mismatched segment ["h","y"].

Example 2:
    Input:  s1 = "action", s2 = "nation"
    Output: [["ac","na"]]
    Explanation: The characters at indices 0 and 1 differ, forming the
    mismatched segment ["ac","na"]. All remaining characters are equal in both
    strings.

Example 3:
    Input:  s1 = "hot", s2 = "hot"
    Output: []
    Explanation: The two strings are identical, so there are no mismatched
    segments.

Constraints:
    - 1 <= s1.length == s2.length <= 100
    - s1 and s2 consist of lowercase English letters.
"""
from typing import List
class Solution:
    def findMismatchedSegments(self, s1: str, s2: str) -> List[List[str]]:
        buff1, buff2 = [], []
        ans = []
        for i in range(len(s1)):
            if s1[i] == s2[i]:
                if len(buff1) > 0:
                    ans.append(["".join(buff1), "".join(buff2)])
                buff1 = []
                buff2 = []
            else:
                buff1.append(s1[i])
                buff2.append(s2[i])
        if len(buff1) > 0:
            ans.append(["".join(buff1), "".join(buff2)])
        return ans