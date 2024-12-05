def initialize_board(size):
    """Initialize an empty chessboard with -1 to indicate unvisited squares."""
    return [[-1 for _ in range(size)] for _ in range(size)]


def is_valid_move(x, y, board):
    """Check if the move is valid: within bounds and not yet visited."""
    size = len(board)
    return 0 <= x < size and 0 <= y < size and board[x][y] == -1


def solve_knights_tour(board, x, y, move_count):
    """Recursively attempt to solve the Knight's Tour problem using backtracking."""
    size = len(board)

    if move_count == size * size:
        return True

    knight_moves = [
        (2, 1),
        (1, 2),
        (-1, 2),
        (-2, 1),
        (-2, -1),
        (-1, -2),
        (1, -2),
        (2, -1),
    ]

    for dx, dy in knight_moves:
        new_x, new_y = x + dx, y + dy
        if is_valid_move(new_x, new_y, board):
            board[new_x][new_y] = move_count
            if solve_knights_tour(board, new_x, new_y, move_count + 1):
                return True
            board[new_x][new_y] = -1  # Backtrack
    return False


def print_board(board):
    """Print the chessboard with the knight's path."""
    size = len(board)
    for row in board:
        print(" ".join(str(cell).rjust(3, " ") for cell in row))


def main():
    size = 8  # Size of the chessboard
    board = initialize_board(size)

    start_x, start_y = 0, 0  # Starting position of the knight
    board[start_x][start_y] = 0  # Initialize the starting position with the first move

    if solve_knights_tour(board, start_x, start_y, 1):
        print("Solution found!")
        print_board(board)
    else:
        print("No solution exists.")


if __name__ == "__main__":
    main()
