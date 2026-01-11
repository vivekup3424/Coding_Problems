from typing import List
class Solution:
    def centeredSubarrays(self,nums:List[int])->int:
        count = 0
        for i in range(len(nums)):
            sum = 0
            num_set : set[int] = set()
            for j in range(i,len(nums)):
                sum += nums[j]
                num_set.add(nums[j])
                if sum in num_set:
                    count+=1
        return count
