from typing import Set
class Solution:
    def smallestRepunitDivByK(self, k: int)-> int:
        seen_rems:Set[int]= set()
        current_num = 0
        while True:
            current_num = current_num * 10 + 1
            current_rem = current_num % k
            if current_rem in seen_rems:
                return -1
            elif current_rem == 0:
                return len(str(current_num))
            else:
                seen_rems.add(current_rem)