from typing import List
import heapq


class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        def calculate_gain(passingStudent, totalStudent):
            return (passingStudent + 1) / (totalStudent + 1) - (
                passingStudent / totalStudent
            )

        max_heap = []
        for passingStudent, totalStudent in classes:
            gain = calculate_gain(passingStudent, totalStudent)
            heapq.heappush(max_heap, (-gain, passingStudent, totalStudent))
        for _ in range(extraStudents):
            current_gain, passingStudent, totalStudent = heapq.heappop(max_heap)
            passingStudent += 1
            totalStudent += 1
            new_gain = calculate_gain(passingStudent, totalStudent)
            heapq.heappush(max_heap, (-new_gain, passingStudent, totalStudent))
        total_passing_students = sum(
            passingStudent for _, passingStudent, _ in max_heap
        )
        return total_passing_students / len(classes)
