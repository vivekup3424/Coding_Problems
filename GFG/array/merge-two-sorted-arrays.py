# Since A has extra space at the end, we can merge from the end of the arrays
# instead of the beginning. This avoids the need to shift elements multiple times.

from typing import List
import unittest


def mergeArrays(a: List[int], b: List[int]):
    i, j = len(a) - 1, len(b) - 1
    for _ in range(len(b)):
        a.append(0)
    k = len(a) - 1
    while i >= 0 and j >= 0:
        if a[i] >= b[j]:
            a[k] = a[i]
            k -= 1
            i -= 1
        else:
            a[k] = b[j]
            k -= 1
            j -= 1
    while i >= 0:
        a[k] = a[i]
        k -= 1
        i -= 1
    while j >= 0:
        a[k] = b[j]
        k -= 1
        j -= 1


class TestMergeInPlace(unittest.TestCase):
    def test_typical_case(self):
        A = [1, 3, 5]
        B = [2, 4, 6]
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2, 3, 4, 5, 6])

    def test_empty_B(self):
        A = [1, 2, 3]
        B = []
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2, 3])

    def test_empty_A(self):
        A = []
        B = [1, 2, 3]
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2, 3])

    def test_both_empty(self):
        A = []
        B = []
        mergeArrays(A, B)
        self.assertEqual(A, [])

    def test_overlapping_values(self):
        A = [1, 2, 3]
        B = [2, 3, 4]
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2, 2, 3, 3, 4])

    def test_single_element_in_A(self):
        A = [1]
        B = [2]
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2])

    def test_single_element_in_B(self):
        A = []
        B = [1]
        mergeArrays(A, B)
        self.assertEqual(A, [1])

    def test_large_arrays(self):
        A = [1, 3, 5, 7, 9]
        B = [2, 4, 6, 8, 10]
        mergeArrays(A, B)
        self.assertEqual(A, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])


if __name__ == "__main__":
    unittest.main()
