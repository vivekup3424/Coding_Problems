class Solution:
    def intersectionWithDuplicates(self, a, b):
        a.sort()
        b.sort()
        s = set()
        i,j = 0,0
        n = len(a)
        m = len(b)
        while i < n and j < m:
            if a[i] == b[j]:
                s.add(a[i])
                i+=1
                j+=1
            elif a[i] < b[j]:
                i+=1
            else:
                j+=1
        answer = []
        for i in s:
            answer.append(i)
        return answer
a = [1, 2, 1, 3, 1]
b = [3, 1, 3, 4, 1]
print(Solution().intersectionWithDuplicates(a,b))