def is_peak(matrix, i, j, n, m):
    val = matrix[i][j]
    if i > 0 and matrix[i - 1][j] >= val:
        return False  # top neighbor
    if i < n - 1 and matrix[i + 1][j] >= val:
        return False  # bottom neighbor
    if j > 0 and matrix[i][j - 1] >= val:
        return False  # left neighbor
    if j < m - 1 and matrix[i][j + 1] >= val:
        return False  # right neighbor
    return True

def stabilize_matrix(matrix, n, m):
    found = True
    while found:
        found = False
        peak_i, peak_j = -1, -1

        # Find the peak cell
        for i in range(n):
            for j in range(m):
                if is_peak(matrix, i, j, n, m):
                    if peak_i == -1 or i < peak_i or (i == peak_i and j < peak_j):
                        peak_i, peak_j = i, j
        
        if peak_i != -1 and peak_j != -1:
            matrix[peak_i][peak_j] -= 1
            found = True

def main():
    import sys
    input = sys.stdin.read
    data = input().split()

    index = 0
    t = int(data[index])
    index += 1
    results = []

    for _ in range(t):
        n = int(data[index])
        m = int(data[index + 1])
        index += 2

        matrix = []
        for i in range(n):
            row = list(map(int, data[index:index + m]))
            matrix.append(row)
            index += m
        
        stabilize_matrix(matrix, n, m)

        result = []
        for row in matrix:
            result.append(' '.join(map(str, row)))
        results.append('\n'.join(result))
    
    print('\n'.join(results))

if __name__ == "__main__":
    main()
