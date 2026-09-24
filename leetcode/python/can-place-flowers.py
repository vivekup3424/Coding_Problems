from typing import List
class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        flowerbed_length = len(flowerbed)
        if(n==0):
            return True
        count = 0
        for i in range(flowerbed_length):
            if(flowerbed[i]==0):
                isLeftZero = (i==0 or flowerbed[i-1]==0)
                isRightZero = (i==flowerbed_length-1 or flowerbed[i+1]==0)
                if isLeftZero and isRightZero:
                    flowerbed[i]=1
                    count+=1
            return count>=n
