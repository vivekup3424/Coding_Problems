from typing import List
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        points.sort(key = lambda point: point[1])
        count,end = 1, points[0][1]
        for i in range(1,len(points)):
            if points[i][0] > end:
                count+=1
                end = points[i][1]
        return count