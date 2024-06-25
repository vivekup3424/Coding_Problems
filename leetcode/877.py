def stoneGame(piles):
    dp = {}
    def dfs(l,r):
        if l>r:
            return 0
        elif (l,r) in dp:
            return dp[(l,r)]
        else:
            return max(piles[l]+dfs(l+1,r),piles[r]+dfs(l,r-1))