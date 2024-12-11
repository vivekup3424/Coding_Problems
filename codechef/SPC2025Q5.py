from typing import DefaultDict


def solve(L, R, A):
    freq = DefaultDict(int)
    for i in A:
        freq[i] += 1
        if freq[i] > 1:
            if L <= 0 <= R:
                return "YES"
            else:
                return "NO"
    currentProduct = 1
    for i in range(0, len(A)):
        for j in range(i + 1, len(A)):
            currentProduct *= A[i] * A[j]
            if currentProduct > R:
                return "NO"
    if L <= currentProduct <= R:
        return "YES"
    else:
        return "NO"


def main():
    T = int(input())
    for _ in range(T):
        _, L, R = map(int, input().split())
        A = list(map(int, input().split()))
        print(solve(L, R, A))


main()
