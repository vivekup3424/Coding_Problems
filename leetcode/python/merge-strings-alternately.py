from typing import List
class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        """
        i = word1
        j = word2
        """
        temp : List[str]= []
        i,j = 0,0
        while i < len(word1) and j < len(word2):
            temp.append(word1[i])
            temp.append(word2[j])
            i+=1
            j+=1
        answer = ''.join(temp)
        if i != len(word1):
            answer += word1[i:]
        if j != len(word2):
            answer += word2[j:]
        return answer