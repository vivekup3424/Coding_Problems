from typing import List, Set
from enum import Enum


class Sequence(Enum):
    DECREASING = 0
    INCREASING = 1
    UNDEFINED = -1


def determine_sequence_type(numbers: List[int]) -> Sequence:
    """Determine if the sequence is increasing, decreasing, or undefined."""
    if numbers[0] > numbers[-1]:
        return Sequence.DECREASING
    elif numbers[0] < numbers[-1]:
        return Sequence.INCREASING
    return Sequence.UNDEFINED


def is_valid_sequence(numbers: List[int], valid_differences: Set[int]) -> bool:
    """Check if the sequence follows the valid difference rules."""
    sequence_type = determine_sequence_type(numbers)

    if sequence_type == Sequence.UNDEFINED:
        return False

    for i in range(len(numbers) - 1):
        if sequence_type == Sequence.DECREASING:
            diff = numbers[i] - numbers[i + 1]
        else:
            diff = numbers[i + 1] - numbers[i]

        if diff not in valid_differences:
            return False

    return True


def try_remove_one_number(values: List[str], valid_differences: Set[int]) -> bool:
    """Try removing one number at a time to see if it creates a valid sequence."""
    for i in range(len(values)):
        temp = values[:i] + values[i + 1 :]
        if len(temp) <= 1:
            continue

        numbers = [int(x) for x in temp]
        if is_valid_sequence(numbers, valid_differences):
            return True

    return False


def count_safe_sequences(filename: str) -> int:
    """Count the number of safe sequences in the input file."""
    valid_differences = {1, 2, 3}
    safe_count = 0

    with open(filename, mode="r") as file:
        for line in file:
            values = line.strip().split()

            if len(values) <= 1:
                continue

            numbers = [int(x) for x in values]

            # Check if sequence is valid as-is
            if is_valid_sequence(numbers, valid_differences):
                safe_count += 1
                continue

            # Try removing one number to make sequence valid
            if try_remove_one_number(values, valid_differences):
                safe_count += 1

    return safe_count


if __name__ == "__main__":
    result = count_safe_sequences("./input")
    print(result)
