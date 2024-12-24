from functools import lru_cache

@lru_cache(None)
def recurse(n):
    if n <= 3:
        return 1
    else:
        return recurse(n//4) + recurse(n//4)
def solve(n):
    print(recurse(n))

t = int(input())
for _ in range(t):
    n = int(input())
    solve(n)
