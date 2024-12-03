import re

with open("./input", "r") as f:
    data = f.read()

matches = re.findall(r"(?:mul\((\d{1,3}),(\d{1,3})\))|(do\(\)|don't\(\))", data)

current_state = True
total = 0
for left, right, state_change in matches:
    match state_change:
        case "do()":
            current_state = True
        case "don't()":
            current_state = False
        case _:
            if current_state:
                total += int(left) * int(right)

print(total)
