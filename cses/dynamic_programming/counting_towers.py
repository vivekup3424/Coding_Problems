t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    oneBlocks = [1] * n
    twoBlocks = [1] * n
    for i in range(1, n):
        oneBlocks[i] = 2 * oneBlocks[i - 1] + twoBlocks[i - 1]
        twoBlocks[i] = oneBlocks[i - 1] + 4 * twoBlocks[i - 1]
    print(oneBlocks[n - 1] + twoBlocks[n - 1])
