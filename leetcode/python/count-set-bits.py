# def count_bits(x):
#     num_bits = 0
#     while x:
#         num_bits += x & 1
#         x >>= 1
#     return num_bits
def count_bits(x):
    num_bits = 0
    while x:
        num_bits += 1
        x &= x - 1
        print(f"num_bits : {num_bits}")
        print(f"x : {x}")


# n = int(input("Enter an integer:\t"))
print(count_bits(13))
