class MinHeap:
    def __init__(self):
        self.heap = []

    def parent(self, i):
        return (i - 1) // 2

    def left_child(self, i):
        return 2 * i + 1

    def right_child(self, i):
        return 2 * i + 2

    def pop(self):
        if len(self.heap) == 0:
            return None
        if len(self.heap) == 1:
            return self.heap.pop()
        root = self.heap[0]
        self.heap[0] = self.heap.pop()
        self.heapify(0)
        return root

    def push(self, value):
        self.heap.append(value)
        currentIdx = len(self.heap) - 1
        while (
            currentIdx > 0
            and self.heap[currentIdx] < self.heap[self.parent(currentIdx)]
        ):
            self.heap[currentIdx], self.heap[self.parent(currentIdx)] = (
                self.heap[self.parent(currentIdx)],
                self.heap[currentIdx],
            )
            currentIdx = self.parent(currentIdx)

    def heapify(self, i):
        left = self.left_child(i)
        right = self.right_child(i)
        smallest = i
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right

        if smallest != i:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self.heapify(smallest)
    def __sizeof__(self) -> int:
        "returns the size of the current minHeap"
        return len(self.heap)

class Solution:
    def hIndex(self,citations):
        minheap = MinHeap()
        for i in citations:
            if i > 0:
                minheap.push(i)
        ans = 0
        while 

def main():
    minheap = MinHeap()
    print("Let's develop an interactive minheap")
    while True:
        print("1. Push\n2. Pop\n3. Print\n4. Exit")
        choice = int(input("Enter your choice: "))
        if choice == 1:
            value = int(input("Enter the value to be pushed: "))
            minheap.push(value)
        elif choice == 2:
            print(f"Popped Value = {minheap.pop()}")
        elif choice == 3:
            print(f"Current MinHeap: {minheap.heap}")
        elif choice == 4:
            break


if __name__ == "__main__":
    main()
