##https://codeforces.com/problemset/problem/1399/D

n,m = map(int,input().split())
q = []
q.append([n,0]) #first element, second steps
while len(q) > 0:
    p = q.pop(0)
    if p[0] < 0:
        continue
    elif p[0] == m:
        print(p[1])
        break
    q.append([p[0]*2,p[1]+1])
    q.append([p[0]-1,p[1]+1])
