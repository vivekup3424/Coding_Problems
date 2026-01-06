from typing import List, Dict
from collections import defaultdict
class Solution:
    def longestConsecutiveSubstring(self, nums: List[int]) -> int:
        prev_element, current_length,max_length = nums[0],0,0
        for num in nums:
            if num - prev_element == 1:
                current_length+=1
                prev_element = num 
            else:
                current_length = 1
                prev_element = num
            max_length = max(max_length,current_length)
        return max_length
    
    def longestConsecutiveWithHashMap(self, nums: List[int])->int:
        if not nums:
            return 0

        map_sequence: Dict[int, int] = defaultdict(int)
        longest = 0
        for num in nums:
            left_sequence_length = map_sequence[num-1]
            right_sequence_length = map_sequence[num+1]
            total_length = right_sequence_length + left_sequence_length + 1
            map_sequence[num] = total_length
            if map_sequence[num-1]:
                map_sequence[num-1] = total_length
            if map_sequence[num+1]:
                map_sequence[num+1] = total_length
            longest = max(longest, total_length)
        return longest
    
    def longestConsecutiveWithHashSet(self, nums: List[int])->int:
        #insert every element in the set
        num_set : set[int]= set()
        for num in nums:
            num_set.add(num)

        return 80085
