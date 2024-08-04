#BEST TIME TO BUY AND SELL STOCKS
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        diff = []
        n = len(prices)
        for i in range(1,n):
            diff.append(prices[i] - prices[i-1])
        print(diff)
        #the below algorithm is Kadane's 
        maxProfit, currentProfit = 0,0
        for d in diff:
            currentProfit += d
            if(currentProfit < 0):
                currentProfit = 0
            maxProfit = max(maxProfit,currentProfit)
        return maxProfit