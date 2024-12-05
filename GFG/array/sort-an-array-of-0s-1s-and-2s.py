from typing import List


class Solution:
    def sort012(self, arr: List[int]) -> List[int]:
        i, j, k = 0, 0, len(arr) - 1
        while j <= k:
            if arr[j] == 0:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
                j += 1
            elif arr[j] == 1:
                j += 1
            elif arr[j] == 2:
                arr[k], arr[j] = arr[j], arr[k]
                k -= 1
            # print(arr)
        return arr


if __name__ == "__main__":
    arr = [0, 1, 2, 0, 1, 2]
    sol = Solution()
    print(sol.sort012(arr))
