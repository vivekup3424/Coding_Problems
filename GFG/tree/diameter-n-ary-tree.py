class Node:
    def __init__(self,x) -> None:
        self.key = x
        self.child = []
    
#utility function to find height of a node
def height(node):
    if node == None:
        return 0
    maxHeight = 0
    for c in node.child:
        maxHeight = max(maxHeight, height(c))
    return 1 + maxHeight

def diamter(root):
    if root is None:
        return 0
    #find the top two highest children
    firstMax, secondMax = 0, 0
    for c in root.child:
        h = height(c)
        if h > firstMax:
            secondMax = firstMax
            firstMax = h
        elif h > secondMax:
            secondMax = h
    
    #find the diameter of each child
    maxDiameter = 0
    for c in root.child:
        maxDiameter = max(maxDiameter, diamter(c))
    return max(maxDiameter, firstMax + secondMax + 1)