class Solution:
    def reverseBits(self, n: int) -> int:
        totalBits = 32
        ans = 0
        while totalBits:
            ans = (ans << 1) | (n&1)
            n >>= 1
            totalBits -= 1
        return ans