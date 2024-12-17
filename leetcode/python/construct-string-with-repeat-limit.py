import heapq
from collections import Counter, UserString


class Solution:
    def repeatLimitedString(self, s: str, repeatLimit: str) -> str:
        # count-sort
        # reverse i.e. z to a
        # for maintaining greedily reverse order, we can make use of maxHeap
        counter = Counter(s)
        maxHeap = [(-ord(key), val) for key, val in counter.items()]
        heapq.heapify(maxHeap)
        print(maxHeap)
        answer = []
        while maxHeap:
            char, cnt = heapq.heappop(maxHeap)
            char = chr(-char)
            current_cnt = min(cnt, int(repeatLimit))
            answer += [char] * current_cnt
            cnt -= current_cnt
            if cnt > 0 and maxHeap:
                next_char, next_cnt = heapq.heappop(maxHeap)
                next_char = chr(-next_char)
                answer += [next_char]
                next_cnt -= 1
                if next_cnt > 0:
                    heapq.heappush(maxHeap, (-ord(next_char), next_cnt))
            heapq.heappush(maxHeap, (-ord(char), cnt))
        print(answer)
        return "SHITT"


def main():
    # userString = input("Please enter an string")
    userString = "zzzzccczaac"
    Solution().repeatLimitedString(s=userString, repeatLimit="3")


if __name__ == "__main__":
    main()
