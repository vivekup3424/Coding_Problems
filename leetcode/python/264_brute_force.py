seive = [False] * 1001


def generatePrimes():
    primes = []
    for i in range(2, 1001):
        if not seive[i]:
            for j in range(i * i, 1001, i):
                seive[j] = True
    for i in range(2, 1001):
        if not seive[i]:
            primes.append(i)
    return primes


def getDivisors(primes, num):
    divisors = []
    for p in primes:
        if num <= 1:
            break
        if num % p == 0:
            divisors.append(p)
            while num % p == 0:
                num //= p
    return divisors


def generateUglyNumbers():
    primes = generatePrimes()
    number = 1
    uglies = []
    while len(uglies) < 1690:
        divisors = getDivisors(primes, number)
        isUgly = all(d in {2, 3, 5} for d in divisors)
        if isUgly:
            uglies.append(number)
        number += 1
    return uglies


class Solution:
    def nthUglyNumber(self, n: int) -> int:
        uglies = generateUglyNumbers()
        return uglies[n - 1]


# Example usage:
solution = Solution()
print(solution.nthUglyNumber(10))  # Output: 12
