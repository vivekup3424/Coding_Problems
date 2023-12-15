#Method 1
class Solution1:
    def minExtraChar(self, s: str, dictionary: List[str])->int:
        words = set(dictionary) #creating an hash-set of words
        n = len(s)
        dp = {n:0} #base case
        def dfs(i):
            if i in dp:
                return dp[i]
            res = 1 + dfs(i+1) #if we don't take the current character
            #get prefix of the string starting from i
            for j in range(i,n):
                if s[i:j+1] in word:
                    res = min(res,dfs(j+1))
            dp[i] = res
            return res
        return dfs(0)
        #Time complexiity = O(n^3)
        #Space complexity = O(n)

#Method 2: Using DP and trie
class Trie:
    def __init__(self):
        self.children = {}
        self.isEnd = False
    def insert(self,word):
        cur = self
        for c in word:
            if c not in cur.children:
                cur.children[c] = Trie()
            cur = cur.children[c]
        cur.isEnd = True
    def isWord(self,word):
        cur = self
        for c in word:
            if c not in cur.children:
                return False
            cur = cur.children[c]
        return cur.isEnd
    def isPrefix(self,word):
        cur = self
        for c in word:
            if c not in cur.children:
                return False
            cur = cur.children[c]
        return True
    def delte(self,word):
        cur = self
        for c in word:
            if c not in cur.children:
                return False
            cur = cur.children[c]
        cur.isEnd = False
        return True
class Solution:
    def minExtraChar(self, s: str, dictionary: List[str])->int:
        n = len(s)
        #new root Trie
        root = Trie()
        for word in dictionary:
            root.insert(word)
        dp = {n:0} #dp-hashset
        def dfs(i):
            if i in dp:
                return dp[i]
            res = 1 + dfs(i+1)
            for j in range(i,n):
                if root.isPrefix(s[i:j+1]):
                    res = min(res,dfs(j+1))
            dp[i] = res
            return res
        return dfs(0)

def main():
