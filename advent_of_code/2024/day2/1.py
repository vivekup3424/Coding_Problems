input = open("./input", mode="r")
safe = 0
data = input.read().split("\n")
validDifferences = {1, 2, 3}
for row in data:
    vals = row.split(" ")
    if len(vals) > 1:
        numbers = [int(x) for x in vals]
    else:
        numbers = [0]
    increasing = -1
    if numbers[0] > numbers[len(numbers) - 1]:
        increasing = 0
    elif numbers[0] < numbers[len(numbers) - 1]:
        increasing = 1
    for i in range(0, len(numbers)):
        if i == len(numbers) - 1 and increasing != -1:
            safe += 1
        elif increasing == 0 and validDifferences.__contains__(
            numbers[i] - numbers[i + 1]
        ):
            # print(f"valid vals = {vals}")
            continue
        elif increasing == 1 and validDifferences.__contains__(
            numbers[i + 1] - numbers[i]
        ):
            # print(f"valid vals = {vals}")
            continue
        else:
            # print(f"invalid vals = {vals}")
            suddenBreak = True
            break

print(safe)
