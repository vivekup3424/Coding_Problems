def z_algorithm(s):
    n = len(s)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i < r:
            z[i] = min(r - i, z[i - l])
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] > r:
            l, r = i, i + z[i]
    return z

s = input()
n = len(s)
z = z_algorithm(s)
periods = []
for i in range(n - 1, 0, -1):
    if z[i] == n - i and n % i == 0:
        periods.append(i)
periods.sort()
print(*periods)