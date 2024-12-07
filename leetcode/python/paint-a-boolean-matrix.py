A = [[1,0,0,1,0],
    [1,0,0,1,1],
    [1,0,0,0,1],
    [0,1,1,1,1],
    [0,0,0,0,1]]

def colorMatrix(A,x,y,prevColor = -1):
    if x < 0 or x >= len(A) or y < 0 or y >= len(A[0])  or (prevColor != -1 and prevColor != A[x][y]) :
        return
    directions = [(-1,0),(1,0),(0,1),(0,-1)]
    for moves in directions:
        colorMatrix(A,x+moves[0],y+moves[1],A[x][y])


colorMatrix(A,0,0)
