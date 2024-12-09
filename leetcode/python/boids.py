import os
import time
import random


def clear_screen():
    """Clears the terminal screen."""
    os.system("cls" if os.name == "nt" else "clear")


def random_motion(num_dots=1000):
    """Simulates random motion of multiple dots in the terminal."""
    rows, cols = 20, 50  # Size of the terminal grid
    dots = [
        [random.randint(0, rows - 1), random.randint(0, cols - 1)]
        for _ in range(num_dots)
    ]

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # Up, Down, Left, Right

    while True:
        # Clear the screen
        clear_screen()

        # Draw the grid
        grid = [[" " for _ in range(cols)] for _ in range(rows)]
        for x, y in dots:
            grid[x][y] = "•"

        for row in grid:
            print("".join(row))

        # Move each dot randomly
        for dot in dots:
            dx, dy = random.choice(directions)
            dot[0] = max(0, min(rows - 1, dot[0] + dx))  # Stay within bounds
            dot[1] = max(0, min(cols - 1, dot[1] + dy))  # Stay within bounds

        time.sleep(0.1)


if __name__ == "__main__":
    random_motion()
