def loopingShit(length,d,div):
    num = d
    for i in range(length):
        print(num % div,end=" ")
        num = 10 * num + d

length,d,div = map(int,input().split())
loopingShit(length,d,div)