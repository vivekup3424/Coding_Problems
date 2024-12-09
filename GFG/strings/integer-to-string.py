def integerToString(number):
    isNegative = False
    if number < 0:
        isNegative, number = True, -1 * number
    digits = []  # stores the number in reverse order
    while number > 0:
        digits.append(chr(ord("0") + number % 10))
        number //= 10
    if isNegative:
        digits.append("-")
    return "0" if len(digits) == 0 else "".join(reversed(digits))


print(integerToString(123))
print(integerToString(-123))
print(integerToString(0))
