class Solution:
    def isMonotonic(self, nums: List[int]) -> bool:
        n = len(nums)
        inc, dec = False, False
        if n <= 2:
            return True
        for i in range(0,n-1):
            if nums[i]<nums[i+1]:
                inc = True
            elif nums[i]>nums[i-1]:
                dec = True
        return (inc or dec) and not (inc and dec) #we want to check whether inc is true or dec is true, but not both are true


arr = [1,2,2,3]
A = Solution()
A.isMonotonic(arr)