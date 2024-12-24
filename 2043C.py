def solve(arr):
    values = set()
    pref = [arr[i] for i in range(len(arr))]
    for i in range(len(arr)):
        values.add(pref[i])
        if i > 0:
            pref[i]+=pref[i-1]
            values.add(pref[i])
    print(values)

t = int(input())
for _ in range(t):
    _ = int(input())
    arr = list(map(int,input().split()))
    solve(arr)