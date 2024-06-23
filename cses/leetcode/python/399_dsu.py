import collections
class Solution(object):
    def caclEquation(self,equations,values,queries):
        #try to do this question using union-find
        #best way to do such question
        #when finding the weight the using union,update it also

        parent = {}
        def find(node):
            if node not in parent:
                parent[node] = (node,1)
            pa,w = parent[node]
            if pa != node: #not found the parent
                node_pa,