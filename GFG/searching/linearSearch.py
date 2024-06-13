#py3 code to do linear search of x in arr[]
#otherwise return 0
"""linear search"""
def linearSearch(arr,n,x):
    for i in range(0,n):
        if(arr[i]==x):
            return i
        return 0
#driver code
arr = [2,3,10,7,8,9]
x = 10
n = len(arr)
m = linearSearch(arr,n,x)
print(m)