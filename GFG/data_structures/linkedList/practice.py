class Node:
    def __init(self,data):
        self.data = data
        self.next = None
class singlyLinkedList:
    def __init__(self):
        self.head = None

    def add_node(self,data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node