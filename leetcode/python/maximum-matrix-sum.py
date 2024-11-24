from typing import List


class Node:
    def __init__(self, val, x, y) -> None:
        self.val = val
        self.x = x
        self.y = y

    def __lt__(self, other):
        return self.val < other.val


class MinHeap:
    def __init__(self):
        self.heap = []

    def parent(self, i):
        return (i - 1) // 2

    def leftChild(self, i):
        return 2 * i + 1

    def rightCild(self, i):
        return 2 * i + 2

    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def heapifyUp(self, i):
        parent = self.parent(i)
        if self.heap[i] < self.heap[parent]:
            self.swap(i, parent)
            self.heapifyUp(parent)

    def heapifyDown(self, i):
        leftChild = self.leftChild(i)
        rightChild = self.rightCild(i)
        minimumElementIndex = i
        if (
            leftChild < len(self.heap)
            and self.heap[leftChild] < self.heap[minimumElementIndex]
        ):
            minimumElementIndex = leftChild
        # similary, cheking for the rightChild
        if (
            rightChild < len(self.heap)
            and self.heap[rightChild] < self.heap[minimumElementIndex]
        ):
            minimumElementIndex = rightChild
        # how doing heapifyDown for the children
        if minimumElementIndex != i:
            self.swap(minimumElementIndex, i)
            self.heapifyDown(minimumElementIndex)


class Solution:
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:
        print(matrix)
        return 0
