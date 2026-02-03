from typing import List
class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: x[1])
        print(intervals)
        end,count = intervals[0][1],1
        for i in range(1,len(intervals)):
            if intervals[i][0] >= end:
                count+=1
                end = intervals[i][1]
        return len(intervals) - count