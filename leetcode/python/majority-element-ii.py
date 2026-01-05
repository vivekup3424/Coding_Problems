from typing import List
class Solution:
    def majorityElement(self,nums: List[int]) -> List[int]:
        first_element, first_freq = -1, 0
        second_element, second_freq = 0, 0
        for num in nums:
            if num == first_element:
                first_freq+=1
            elif num == second_element:
                second_freq+=1