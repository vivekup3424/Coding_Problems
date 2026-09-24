from typing import List
class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        flower_length = len(flowerbed)
        if flower_length == 0:
            return True
        #start from 0
        count = 0
        temp = [flowerbed[i] for i in range(n)]
        for i in range(0,flower_length):
            if i == 0 or temp[i-1] == 0:
                count+=1
                flowerbed

