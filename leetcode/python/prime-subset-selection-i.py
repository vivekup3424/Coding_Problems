"""
Prime Subset Selection I
https://leetcode.com/problems/prime-subset-selection-i/

You are given two integers n and s.

Consider all prime numbers less than or equal to n. Select some of these
primes such that:
    - The sum of the selected primes is less than or equal to s.
    - The number of selected primes is maximized.
    - Each prime can be selected at most once.

Return an integer array containing the selected primes in increasing order.
If multiple optimal selections exist, return any of them.

If no prime can be selected, return an empty array.

A prime number is a natural number greater than 1 with only two factors, 1
and itself.
"""
from typing import List
class Solution:
    def maxPrimes(self, n: int, s: int) -> List[int]:
        sieve = [True for _ in range(n+1)]
        sieve[0] = False
        sieve[1] = False
        for i in range(2, int(n**0.5)+1):
            if sieve[i]:
                for p in range(i*i, n+1, i):
                    sieve[p] = False

        primes =  [i for i, prime in enumerate(sieve) if prime]

        ans = []
        for prime in primes:
            if(sum(ans)+prime <= s):
                ans.append(prime)

        return ans
