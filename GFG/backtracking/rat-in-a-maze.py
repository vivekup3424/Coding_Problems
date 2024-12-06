maze = [[1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1]]

# rat can move through 1, but can't move through 0

# moves are left,right,up,down
moves = [[-1, 0], [1, 0], [0, 1], [0, -1]]
total_moves = []


def dfs(x, y, path, maze):
    rows = len(maze)
    cols = len(maze[0])
    if x == rows - 1 and y == cols - 1:
        total_moves.append(path)
        return
    if x < 0 or x >= rows or y < 0 or y >= cols or maze[x][y] == 0:
        return
    maze[x][y] = 0
    for dx, dy in moves:
        newx = x + dx
        newy = y + dy
        dfs(newx, newy, path + [(newx, newy)], maze)


dfs(0, 0, [(0, 0)], maze)
for path in total_moves:
    print(path)
