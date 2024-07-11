def isDistint(num):
    # convert num to a string
    num = str(num)
    return len(num) == len(set(num))


l, r = map(int, input().split())
found = False
for i in range(l,r+1):
    if isDistint(i):
        print(i)
        found = True
        break
if not found:
    print(-1)
