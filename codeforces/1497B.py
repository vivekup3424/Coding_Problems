import sys

def input_vector(n):
    return list(map(int, input().split()))

def output_vector(v):
    print(*v)

def main():
    # Redirecting standard input and output to files
    sys.stdin = open('input.txt', 'r')
    sys.stdout = open('output.txt', 'w')

    T = int(input())
    for _ in range(T):
        n, m = map(int, input().split())
        v = input_vector(n)
        hash_map = {}
        for i in range(n):
            hash_map[v[i]] = hash_map.get(v[i], 0) + 1

        sets = []
        for num in hash_map:
            temp = [num]
            hash_map[num] -= 1
            if hash_map[num] == 0:
                del hash_map[num]
            
            for num2 in hash_map:
                if (num2 + temp[-1]) % m == 0:
                    temp.append(num2)
                    hash_map[num2] -= 1
                    if hash_map[num2] == 0:
                        del hash_map[num2]
            sets.append(temp)

        print(len(sets))

if __name__ == "__main__":
    main()
