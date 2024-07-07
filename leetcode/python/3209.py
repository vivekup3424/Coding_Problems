from typing import List
from collections import defaultdict

nums = [1,2,3]
k = 2
map = defaultdict(int)
count = 0
n = len(nums)
for i in range(n-1,-1,-1):
    if nums[i]==k:
        count+=1
    map2 = defaultdict(int)
    for key,val in map.items():
        if key & nums[i] >= k:
            count+=val
        map2[key & nums[i]] += val
    map2[nums[i]] += 1
    map = map2
print(count)
