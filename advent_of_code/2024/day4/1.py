input = open("./input", mode="r")
# convert input to matrix of characters
input = input.read().strip().split("\n")
rows, cols = len(input), len(input[0])
count = 0
X_indices = []
for i in range(rows):
    for j in range(cols):
        if input[i][j] == "X":
            X_indices.append((i, j))
for indices in X_indices:
    x, y = indices[0], indices[1]
    # search horizontally-front
    if (
        y + 3 < cols
        and input[x][y + 1] == "M"
        and input[x][y + 2] == "A"
        and input[x][y + 3] == "S"
    ):
        count += 1
    # search horizontally-back
    if (
        y - 3 >= 0
        and input[x][y - 1] == "M"
        and input[x][y - 2] == "A"
        and input[x][y - 3] == "S"
    ):
        count += 1
    # search vertically-down
    if (
        x + 3 < rows
        and input[x + 1][y] == "M"
        and input[x + 2][y] == "A"
        and input[x + 3][y] == "S"
    ):
        count += 1
    # search vertically-up
    if (
        x - 3 >= 0
        and input[x - 1][y] == "M"
        and input[x - 2][y] == "A"
        and input[x - 3][y] == "S"
    ):
        count += 1
    # search diagonally-down
    if (
        x + 3 < rows
        and y + 3 < cols
        and input[x + 1][y + 1] == "M"
        and input[x + 2][y + 2] == "A"
        and input[x + 3][y + 3] == "S"
    ):
        count += 1
    # search diagonally-up
    if (
        x - 3 >= 0
        and y - 3 >= 0
        and input[x - 1][y - 1] == "M"
        and input[x - 2][y - 2] == "A"
        and input[x - 3][y - 3] == "S"
    ):
        count += 1

print(count)
