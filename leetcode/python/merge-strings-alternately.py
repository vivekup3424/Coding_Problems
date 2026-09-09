from typing import List
class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        """
        i = word1
        j = word2
        """
        temp  = ""
        max_length = max(len(word1),len(word2))
        for i in range(max_length):
            if(i < len(word1)):
                temp += word1[i]
            if(i < len(word2)):
                temp += word2[i]
            i+=1
        return temp