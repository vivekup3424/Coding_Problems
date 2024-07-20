class Solution:
    def getSmallestString(self, s: str) -> str:
        arr = list(s)
        for i in range(1, len(arr)):
            if (int(arr[i - 1]) & 1 == int(arr[i]) & 1) and int(arr[i - 1]) > int(arr[i]):
                arr[i], arr[i - 1] = arr[i - 1], arr[i]
                break
        return "".join(arr)