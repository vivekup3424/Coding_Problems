MOD = 10**9 + 7

def max_sub_array_sum(arr):
    max_so_far = float('-inf')
    max_ending_here = 0
    start = 0
    end = 0
    s = 0
    
    for i in range(len(arr)):
        max_ending_here += arr[i]
        
        if max_so_far < max_ending_here:
            max_so_far = max_ending_here
            start = s
            end = i
        
        if max_ending_here < 0:
            max_ending_here = 0
            s = i + 1
    
    return max_so_far

def main():
    t = int(input())
    
    for _ in range(t):
        n, k = map(int, input().split())
        arr = list(map(int, input().split()))
        
        max_sum = max_sub_array_sum(arr)
        total = sum(arr) * ((2 ** (k + 1)) * max_sum + 1) % MOD
        
        print(max_sum)

if __name__ == "__main__":
    main()
