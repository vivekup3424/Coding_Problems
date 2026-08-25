"""
151. Reverse Words in a String
https://leetcode.com/problems/reverse-words-in-a-string/

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will
be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between
two words. The returned string should only have a single space separating the
words. Do not include any extra spaces.

Example 1:
    Input:  s = "the sky is blue"
    Output: "blue is sky the"

Example 2:
    Input:  s = "  hello world  "
    Output: "world hello"
    Explanation: Your reversed string should not contain leading or trailing
    spaces.

Example 3:
    Input:  s = "a good   example"
    Output: "example good a"
    Explanation: You need to reduce multiple spaces between two words to a
    single space in the reversed string.

Constraints:
    - 1 <= s.length <= 10^4
    - s contains English letters (upper-case and lower-case), digits, and
      spaces ' '.
    - There is at least one word in s.
"""
class Solution:
    def reverseWords(self, s: str) -> str:
        words = []
        i = 0
        while(i < len(s)):
            if(s[i]==' '):
                i+=1
                continue
            word = ""
            for j in range(i,len(s)):
                if(s[j]==' '):
                    break
                word+=s[j];
            words.append(word)
            i = j+1
        print("list of words")
        print(words)
        answer = ""
        for i in range(len(words)-1,-1,-1):
            if(i!=len(words)-1):
                answer+=" "
            answer+=words[i];
        return answer;
