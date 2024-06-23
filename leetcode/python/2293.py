class Solution:
    def value(nums, l, r, isMin) -> int:
        if l==r:
            return nums[l]
        if isMin:
            return min(value(nums,l,(r-l)/2), value(nums,l + (r-l)/2 + 1, r))
        else:
            return max(value(nums,l,(r-l)/2), value(nums,l + (r-l)/2 + 1, r))
    def minMaxGame(self, nums: List[int]) -> int:
        return value()