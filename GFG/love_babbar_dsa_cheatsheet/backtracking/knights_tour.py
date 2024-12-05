def initialize_board(size):
    """initialize empty chessboard with -1 to indicate unvisited squares"""
    return [[-1 for _ in range(size)] for _ in range(size)]


def is_valid_move(x, y, board):
    """Check if the movie is valid: within bounds and not yet visited"""
    size = len(board)
    return 0 <= x < size and 0 <= y < size and board[x][y] == -1


def knight_tour(board, x, y, move_count):
    size = len(board)
    if move_count == size * size:
        print(f"board = {board}")
        return True
    knight_moves = [
        (1, 2),
        (-1, 2),
        (1, -2),
        (-1, -2),
        (2, 1),
        (2, -1),
        (-2, 1),
        (-2, -1),
    ]
    for dx, dy in knight_moves:
        new_x, new_y = x + dx, y + dy
        if is_valid_move(new_x, new_y, board):
            board[new_x][new_y] = move_count
            if knight_tour(board, new_x, new_y, move_count + 1):
                return True
            board[new_x][new_y] = -1
    return False


board = initialize_board(8)
knight_tour(board, 0, 0, 0)
