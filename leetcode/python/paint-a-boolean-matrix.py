import random
import time
import copy
import os


def printMatrix(matrix):
    """Prints the matrix."""
    for row in matrix:
        print("".join(row))
    print()


def colorMatrix(matrix, x, y, prevColor=None):
    """
    Flood-fill the matrix with animation.
    """
    if x < 0 or x >= len(matrix) or y < 0 or y >= len(matrix[0]):
        return
    if prevColor is None:
        prevColor = matrix[x][y]
    if matrix[x][y] != prevColor:
        return
    newColor = "░" if matrix[x][y] == "█" else "█"
    matrix[x][y] = newColor

    # Clear screen and display updated matrix
    os.system("clear")
    printMatrix(matrix)
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    for dx, dy in directions:
        colorMatrix(matrix, x + dx, y + dy, prevColor)


def main():
    # Original matrix
    original_matrix = [
        [
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
        ],
        [
            "█",
            "░",
            "░",
            "░",
            "█",
            "█",
            "░",
            "░",
            "█",
            "█",
            "█",
            "█",
            "░",
            "░",
            "█",
            "█",
            "█",
            "█",
            "░",
            "░",
        ],
        [
            "░",
            "█",
            "█",
            "█",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "█",
            "█",
            "█",
            "░",
            "█",
            "█",
            "█",
            "█",
        ],
        [
            "█",
            "░",
            "░",
            "█",
            "█",
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
        ],
        [
            "░",
            "░",
            "░",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "░",
            "█",
            "░",
            "░",
            "░",
            "░",
            "░",
            "█",
        ],
    ]
    frame_delay = 1 / 30
    while True:
        # Reset matrix
        A = original_matrix
        start_x = random.randint(0, len(A) - 1)
        start_y = random.randint(0, len(A[0]) - 1)
        colorMatrix(A, start_x, start_y)
        time.sleep(frame_delay)


main()
