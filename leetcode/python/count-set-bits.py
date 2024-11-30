def count_bits(x):
    num_bits = 0
    while x:
        num_bits += x & 1
        x >>= 1
    return num_bits


# n = int(input("Enter an integer:\t"))
print(count_bits(13))
