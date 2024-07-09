# Initialize the sieve array
seive = [False] * 1001


# Function to generate prime numbers using the sieve of Eratosthenes
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


# Function to get divisors of a number using the list of primes
def getDivisors(primes, num):
    divisors = []
    for p in primes:
        if p * p > num:
            break
        if num % p == 0:
            while num % p == 0:
                num //= p
            divisors.append(p)
    if num > 1:
        divisors.append(num)
    return divisors


# Function to generate the first 1690 ugly numbers
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


# Class to solve the problem of finding the nth ugly number
class Solution:
    def nthUglyNumber(self, n: int) -> int:
        uglies = generateUglyNumbers()
        return uglies[n - 1]
