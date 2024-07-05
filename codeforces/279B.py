"""
Input

The first line contains two integers n and t (1 ≤ n ≤ 10^5; 
1 <= t≤ 10^9) — the number of books and the number of free minutes Valera's got. The second line contains a sequence of n integers a1, a2, ..., an (1 ≤ ai ≤ 104), where number ai shows the number of minutes that the boy needs to read the i-th book.
"""


n,t = map(int,input().split())
books = list(map(int,input().split()))
count = 0
for i in range(n):
    if t >= books[i]:
        t -= books[i]
        count += 1
    else:
        break   
print(count)