class DSU():
    def __init__(self,n):
        self.vertices = n
        self.parents = [i for i in range(0,self.vertices+1)]    
    def find(self,i):
        if self.parents[i] != i:
            self.parents[i] = self.find(self.parents[i])
        return self.parents[i]
    def union(self,i,j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if root_i < root_j:
                self.parents[root_j] = root_i
            else:
                self.parents[root_i] = root_j
