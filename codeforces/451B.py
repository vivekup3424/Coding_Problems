def isSorted(v):
    n = len(v)
    for i in range(n):
        if i+1 < n and v[i]>v[i+1]:
            return False
    return True

n = int(input())
v = list(map(int,input().split()))
start,end = 0,0
for i in range(n):
    if i+1 < n and v[i] > v[i+1]:
        start = i
        end = i+1
        while end+1 < n and v[end]>v[end+1]:
            end+=1
        break
#reverse the array between start and end
v[start:end+1] = reversed(v[start:end+1])
if isSorted(v):
    print("yes")
    print(start+1,end+1)
else:
    print("no")
