input = open("./input1", mode="r")
arr = input.read().split("\n")
sum = 0
stream1 = []
stream2 = []
for line in arr:
    word = line.split("   ")
    if len(word) == 2:
        stream1.append(int(word[0]))
        stream2.append(int(word[1]))

stream1.sort()
stream2.sort()
for i in range(len(stream1)):
    sum += abs(stream1[i] - stream2[i])
print(sum)
