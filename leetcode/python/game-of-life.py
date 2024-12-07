# Game of life implementation

import random
import shutil
import copy
import time


def generateMatrix(rows, cols):
    """
    Generates a matrix with the given dimensions (rows x cols)
    filled with the characters '█' and '░' randomly.

    Args:
        rows (int): Number of rows in the matrix.
        cols (int): Number of columns in the matrix.

    Returns:
        list: A matrix of size rows x cols with '█' and '░'.
    """
    return [[random.choice(["█", "░"]) for _ in range(cols)] for _ in range(rows)]


def printMatrix(A):
    """
    Prints the matrix in a visually pleasing format.

    Args:
        A (list): The matrix to print.
    """
    for row in A:
        print("".join(row))
    print()


def numberOfLiveNeighbors(matrix, x, y):
    rows, cols = len(matrix), len(matrix[0])
    directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    live_neighbors = 0
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < rows and 0 <= ny < cols:  # Check bounds
            live_neighbors += matrix[nx][ny] == "█"
    return live_neighbors


def GameOfLife():
    # Example usage
    terminal_width, terminal_height = shutil.get_terminal_size()
    rows, cols = random.randint(10, terminal_height - 2), random.randint(
        10, terminal_width - 2
    )  # Dimensions of the matrix
    matrix = generateMatrix(rows, cols)
    temp = copy.deepcopy(matrix)
    time_delay = 1 / 14
    while True:
        print("\033[H\033[J")
        printMatrix(matrix)
        for i in range(0, rows):
            for j in range(0, cols):
                if matrix[i][j] == "█" and numberOfLiveNeighbors(matrix, i, j) < 2:
                    temp[i][j] = "░"
                elif matrix[i][j] == "█" and numberOfLiveNeighbors(matrix, i, j) in {
                    2,
                    3,
                }:
                    continue
                elif matrix[i][j] == "█" and numberOfLiveNeighbors(matrix, i, j) > 3:
                    temp[i][j] = "░"
                elif matrix[i][j] == "░" and numberOfLiveNeighbors(matrix, i, j) == 3:
                    temp[i][j] = "█"
        matrix = temp
        time.sleep(time_delay)


GameOfLife()
