class Solution:
    def mergeArrays(self, a, b):
        # a contains first sorted elements,
        # b contains the other part of the sorted elements
        # without using extra memory
        i, j = 0, 0
        while i < len(a)
            print(f"i = {i}, j = {j}")
            print(a)
            print(b)
            if a[i] <= b[j]:
                i += 1
            else:
                a[i], b[j] = b[j], a[i]


def main():
    # n = int(input())
    a = [2, 4, 7, 10]
    # m = int(input())
    b = [2, 3]
    ob = Solution()
    ob.mergeArrays(a, b)


if __name__ == "__main__":
    main()
