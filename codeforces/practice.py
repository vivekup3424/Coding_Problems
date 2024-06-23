import re
s = input()

integers = [int(match.group(0)) for match in re.finditer(r'-?\d+', s)]
#print(integers)
sum = 0
for i in integers:
    sum += i

print(sum)