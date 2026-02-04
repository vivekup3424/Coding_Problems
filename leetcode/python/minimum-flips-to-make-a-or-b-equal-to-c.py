class Solution:
    def minFlips(self, a: int,b: int, c: int) -> int:
        bits_a = [0 for _ in range(30)] #think about how did you get this 30
        bits_b = [0 for _ in range(30)]
        bits_c = [0 for _ in range(30)]
        for i in range(30):
            if 1 << i & a:
                bits_a[i] = 1
            if 1 << i & b:
                bits_b[i] = 1
            if 1 << i & c:
                bits_c[i] = 1
        print(f"bits_a = {bits_a}")
        print(f"bits_b = {bits_b}")
        print(f"bits_c = {bits_c}")
        sum = 0
        for i in range(30):
            if bits_c[i]==0:
                sum += bits_a[i] + bits_b[i]
            elif bits_c[i]==1 and bits_a[i]==0 and bits_b[i]==0:
                sum+=1
        return sum