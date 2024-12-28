from typing import List
class Solution:
    def findTriplets(self, arr: List[int]) -> List[List[int]]:
        arr.sort()
        answer = []
        for i in range(len(arr) - 2):
            if i > 0 and arr[i] == arr[i - 1]:
                continue  # Skip duplicate elements
            j, k = i + 1, len(arr) - 1
            while j < k:
                triplet_sum = arr[i] + arr[j] + arr[k]
                if triplet_sum == 0:
                    answer.append([arr[i], arr[j], arr[k]])
                    while j < k and arr[j] == arr[j + 1]:
                        j += 1  # Skip duplicate elements
                    while j < k and arr[k] == arr[k - 1]:
                        k -= 1  # Skip duplicate elements
                    j += 1
                    k -= 1
                elif triplet_sum > 0:
                    k -= 1
                else:
                    j += 1
        return answer