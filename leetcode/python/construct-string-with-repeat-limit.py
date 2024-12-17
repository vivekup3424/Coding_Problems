import heapq
from collections import Counter


class Solution:
    def repeatLimitedString(self, s: str, repeatLimit: str) -> str:
        # count-sort
        # reverse i.e. z to a
        # for maintaining greedily reverse order, we can make use of maxHeap
        counter = Counter(s)
        maxHeap = [(-ord(key), val) for key, val in counter.items()]
        heapq.heapify(maxHeap)
        for key, val in counter.items():
            heapq.heappush(maxHeap, (-ord(key), -val))
        print(maxHeap)
        return "SHITT"


def main():
    userString = input("Please enter an string")
    Solution().repeatLimitedString(s=userString, repeatLimit="3")


if __name__ == "__main__":
    main()
