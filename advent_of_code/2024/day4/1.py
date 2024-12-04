input = open("./input", mode="r")
# convert input to matrix of characters
input = input.read().strip().split("\n")
rows, cols = len(input), len(input[0])
print(rows, cols)
count = 0
X_indices = []
for i in range(rows):
    for j in range(cols):
        if input[i][j] == "X":
            X_indices.append((i, j))
for indices in X_indices:
    x, y = indices[0], indices[1]
    word = "MAS"
    # search horizontally-front
    k = 0
    for j in range(y + 1, cols):
        if input[x][j] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
    # search horizontally-back
    k = 0
    for j in range(y - 1, -1, -1):
        if input[x][j] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
    # search vertically-down
    k = 0
    for j in range(x + 1, rows):
        if input[j][y] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
    # search vertically-up
    k = 0
    for j in range(x - 1, -1, -1):
        if input[j][y] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
    # search horizontally-down
    k = 0
    temp_x, temp_y = x + 1, y + 1
    while temp_x < rows and temp_y < cols:
        if input[temp_x][temp_y] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
        temp_x += 1
        temp_y += 1
    # search horizontally-up
    k = 0
    temp_x, temp_y = x - 1, y - 1
    while temp_x >= 0 and temp_y >= 0:
        if input[temp_x][temp_y] == word[k]:
            k += 1
        if k == len(word):
            count += 1
            break
        temp_x += -1
        temp_y += -1

print(count)
