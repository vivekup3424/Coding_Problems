from typing import List
class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        count = 0
        for i in range(0,len(flowerbed),2):
            if((i == 0 or flowerbed[i-1] == 0) and flowerbed[i]==0):
                count+=1
            if count == n:
                return True
        return False
