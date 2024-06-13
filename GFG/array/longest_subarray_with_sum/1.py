from typing import List

#Brute force
def getLongestSubarray(a: [int], p : int)-> int:
    n = len(a)
    length = 0

    for i in range(n): #starting index
        for j in range(i,n): #ending index
            sum = 0
            for k in range(i,j+1):
                s += a[k]
            if sum == p:
                length = max(length, j - i + 1)
    return length

