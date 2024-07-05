n = int(input())
maxi,mini,maxiCount,miniCount = 0,10**9,0,0

v = list(map(int,input().split()))
for i in v:
    if maxi == i:
        maxiCount+=1
    elif (i > maxi):
        maxi = i
        maxiCount = 1
    if mini == i:
        miniCount+=1
    elif i < mini:
        mini = i
        miniCount = 1

if maxi == mini:
    print(0,(n*(n-1))//2)
else:
    print(maxi-mini, maxiCount*miniCount)