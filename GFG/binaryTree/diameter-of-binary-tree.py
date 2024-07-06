"""find the diameter of a binary tree"""

class Node:
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

#get the height of tree from Node node
def height(node):
    if node is None:
        return 0
    else:
        return 1 + max(height(node.left, node.right))

def diameter(root):
    if root is None:
        return 0
    lheight = height(root.left)
    rheight = height(root.right)
    ldiameter = diameter(root.left)
    rdiamter = diameter(root.right)
    return max(lheight+rheight+1,max(ldiameter,rdiamter))