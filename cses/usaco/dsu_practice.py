import sys
class DSU:
    """Disjoint Set union class"""
    def __init__(self,vertices):
        self.parents = [i for i in range(0,vertices+1)]
    def find(self,i):
        if self.parents[i] != i:
            self.parents[i] = self.find(self.parents[i])
        return self.parents[i]
    def union(self,i,j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i == root_j:
            return
        elif root_i < root_j:
            self.parents[j] = root_i
        else:
            self.parents[i] = root_j

input = sys.stdin.readline

N,Q = int(input().split())
dsu = DSU(N)
for _ in range(Q):
    t,v,u = int(input().split())
    if  t == 0:
        dsu.union(v,u)
    elif t==1:
        print(dsu.find(v)==dsu.find(u)) 


