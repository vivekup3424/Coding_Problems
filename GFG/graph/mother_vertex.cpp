/*A mother vertex in a graph G = (V, E) is a vertex v such 
that all other vertices in G can be reached by a path from v*/

/*How to find a mother vertex? 

        Case 1: Undirected Connected Graph: In this case, all the vertices 
        are mother vertices as we can reach all the other nodes in the graph.

        Case 2: Undirected/Directed Disconnected Graph: In this case, there 
        are no mother vertices as we cannot reach to all the other nodes in the graph.

        Case 3: Directed Connected Graph: In this case, we have to find a 
        vertex -v in the graph such that we can reach all the other nodes 
        in the graph through a directed path.*/

/*
Naive Approach: To solve the problem follow the below idea:

    A trivial approach will be to perform a DFS/BFS on all the 
    vertices and find whether we can reach all the vertices from that vertex. 
    
Time Complexity: O(V * (E+V))
Auxiliary Space: O(1) It will be O(V) if the stack space for DFS is considered
or if we use a BFS.*/

    
