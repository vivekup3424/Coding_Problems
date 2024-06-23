import collections
class Solution(object):
    def calcEquation(self, equations, values, queries):
        graph = {}
        def build_graph(equations,values):
            def add_edge(f,t,val):
                if f in graph:
                    graph[f].append((t,val))
                else:
                    graph[t] = [(t,val)]
            for vertices,value in zip(equations,values):
                f,t = vertices
                add_edge(f,t,value)
                add_edge(t,f,1/value)
        
        def find_path(query):
            b,e = query
            if b not in graph or e not in graph:
                return -1.0
            q = collections.deque([b,1.0]) #bfs
            visited = set()
            while q:
                front,current_product = q.popleft()
                if front == e:
                    return current_product
                visited.add(front)
                for neighbor,value in graph[front]:
                    if neighbor not in visited:
                        q.append((neighbor,current_product*value))
            
            return -1.0
        build_graph(equations,values)
        return [find_path(q) for q in queries]