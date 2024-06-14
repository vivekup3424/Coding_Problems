import random

# Constants
MAX_LENGTH = 5 * 10**4
MAX_VALUE = 10**9

# Generate the array
arr = [random.randint(0, MAX_VALUE) for _ in range(MAX_LENGTH)]

# Print the array in a format that can be used as input for your C++ program
print(MAX_LENGTH)
print(" ".join(map(str, arr)))
