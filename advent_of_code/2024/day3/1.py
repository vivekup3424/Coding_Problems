import re

with open("./input", "r") as f:
    data = f.read()

print(
    sum(
        (
            int(value_a) * int(value_b)
            for value_a, value_b in re.findall(r"mul\((\d{1,3}),(\d{1,3})\)", data)
        )
    )
)
