class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        l,r = 0,0
        n = len(nums)
        sum,counter = 0,0
        while r < n:
            while l < n and sum >= goal:
                counter += (sum == goal)
                sum -= nums[l]
                l+=1
            sum += nums[r]
            r+=1
            counter += (sum ==  goal)
        return counter