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
z = z_algorithm(s)
ans = len(s)  # Counting the single-character substrings
for i in range(1, len(s)):
    ans += z[i]
print(ans)
