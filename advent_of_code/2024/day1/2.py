from collections import defaultdict

input = open("./input1", mode="r")
arr = input.read().split("\n")
sum = 0
streamSet1 = set()
stream2 = defaultdict(int)
for line in arr:
    word = line.split("   ")
    if len(word) == 2:
        streamSet1.add(int(word[0]))
        stream2[int(word[1])] += 1

for i in streamSet1:
    if i in stream2:
        sum += i * stream2[i]
print(sum)
