from typing import List
class Solution:
    def maxAreaBrute(self, height: List[int])->int:
        n = len(height)
        max_area = 0
        for i in range(n):
            for j in range(i,n):
                max_area = max(max_area, min(height[i],height[j])*(j-i+1))
        return max_area
    """
    The Core Logic:
        At every step, the area is limited by the shorter wall.

        If I keep the shorter wall and move the taller one, the width decreases, and the height remains capped by the shorter wall. This guarantees a smaller area.

        Therefore, my only chance to find a larger area is to move the shorter pointer inward, hoping to find a taller wall.

    Handling Equal Heights:
        If both walls are the same height, both are acting as bottlenecks.

        Keeping either of them limits the potential height to that value, while the width shrinks.

        To find a larger area, I need both ends of the container to be higher than the current value.

        Therefore, I can safely move both pointers inward, effectively discarding both lines."
    """

    def maxArea(self, height: List[int])->int:
        left,right = 0, len(height)-1
        max_area = 0
        while left < right:
            current_area = min(height[left], height[right]) * (right-left)
            max_area = max(max_area,current_area)
            if height[left] < height[right]:
                left+=1
            elif height[right] < height[left]:
                right-=1
            else:
                left+=1
                right-=1
        return max_area