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