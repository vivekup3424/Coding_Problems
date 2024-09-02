from typing import List
import heapq

class Solution:
    class Factor:
        def __init__(self, a: float, e: int, d: int):
            self.damageToHealthRatio = a
            self.endurance = e
            self.damage = d

    class CustomComparator:
        def __call__(self, a, b ) -> bool:
            if a.damageToHealthRatio < b.damageToHealthRatio:
                return True
            elif a.endurance > b.endurance:
                return True
            else:
                return a.damage < b.damage

    def minDamage(self, power: int, damage: List[int], health: List[int]) -> int:
        n = len(damage)
        times = [0] * n
        damageHealthRatio = [0.0] * n
        totalDPS = 0

        maxHeap = []

        for i in range(n):
            times[i] = (health[i] + power - 1) // power
            damageHealthRatio[i] = float(damage[i]) / float(health[i])
            totalDPS += damage[i]
            heapq.heappush(maxHeap, (damageHealthRatio[i], times[i], damage[i]))

        sum_damage = 0

        while maxHeap:
            A = heapq.heappop(maxHeap)
            sum_damage += totalDPS * A[1]
            totalDPS -= A[2]

        return sum_damage

# Example usage
if __name__ == "__main__":
    solution = Solution()
    damage = [1, 2, 3, 4]
    health = [4, 5, 6, 8]
    power = 4
    print(solution.minDamage(power, damage, health))

