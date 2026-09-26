class Solution:
    def canMakeEqual(self, source: list[int], target: list[int]) -> bool:
        if len(source) != len(target):
            return False
        return sum(source) == sum(target)
