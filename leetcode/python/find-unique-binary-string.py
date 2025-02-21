from typing import List
class Solution:
    def convertToDecimal(self,num: str)->int:
        val = 0
        p = 1
        for i in range(len(num)-1,-1,-1):
            val = val + (num[i]=='1')*p
            p *= 2
        return val
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        #convert every elemets to its decimal representation
        decimalReprestation = []
        for num in nums:
            decimalReprestation.append(self.convertToDecimal(num))
        print(decimalReprestation)

def main():
    A = Solution()
    nums = ["111","011","001"]
    A.findDifferentBinaryString(nums)

main()