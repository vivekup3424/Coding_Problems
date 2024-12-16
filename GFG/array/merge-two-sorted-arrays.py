# Since A has extra space at the end, we can merge from the end of the arrays
# instead of the beginning. This avoids the need to shift elements multiple times.

from typing import List


class Solution:
    def mergeArrays(self, a: List[int], b: List[int]):
        i, j = len(a) - 1, len(b) - 1
        for _ in range(len(b)):
            a.append(0)
        k = len(a) - 1
        while i >= 0 and j >= 0:
            if a[i] >= b[j]:
                a[k] = a[i]
                k -= 1
                i -= 1
            else:
                a[k] = b[j]
                k -= 1
                j -= 1
        while i >= 0:
            a[k] = a[i]
            k -= 1
            i -= 1
        while j >= 0:
            a[k] = b[j]
            k -= 1
            j -= 1
        return a


def main():
    # n = int(input())
    a = [2, 4, 7, 10]
    # m = int(input())
    b = [2, 3]
    ob = Solution()
    print(ob.mergeArrays(a, b))


if __name__ == "__main__":
    main()
