def maxHeightOfTriangle(red: int, blue: int) -> int:
    height1 = 0
    height2 = 0
    balls = 1
    red1 = red
    blue1 = blue
    while(True):
        if blue < balls :
            break
        blue -= balls
        balls+=1
        height1+=1
        if red < balls:
            break
        red -= balls
        balls+=1
        height1+=1
    balls = 1
    while(True):
        if red1 < balls :
            break
        red1 -= balls
        balls+=1
        height2+=1
        if blue1 < balls:
            break
        blue1 -= balls
        balls+=1
        height2+=1
    print(max(height1,height2))
    return max(height1,height2)
    


maxHeightOfTriangle(4,9)
