//Union-Find Algorithm can be used to check whether an 
//undirected graph contains cycle or not

/*
Follow the below steps to implement the idea:

    Initially create a parent[] array to keep track of the subsets.
    Traverse through all the edges:
        Check to which subset each of the nodes belong to by finding the 
        parent[] array till the node and the parent are the same.
        If the two nodes belong to the same subset then they belong to a cycle.
        Otherwise, perform union operation on those two subsets.
    If no cycle is found, return false.
*/

// A union-find algorithm to detect cycle in a graph
#include <bits/stdc++.h>
using namespace std;

// a structure to represent an edge in graph
class Edge {
public:
	int src, dest;
};

// a structure to represent a graph
class Graph {
public:
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges
	Edge* edge;
};

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph();
	graph->V = V;
	graph->E = E;

	graph->edge = new Edge[graph->E * sizeof(Edge)];

	return graph;
}

// A utility function to find the subset of an element i
int find(int parent[], int i)
{
	if (parent[i] == i)
		return i;
	return find(parent, parent[i]);
}

// A utility function to do union of two subsets
void Union(int parent[], int x, int y) { parent[x] = y; }

// The main function to check whether a given graph contains
// cycle or not
int isCycle(Graph* graph)
{
	// Allocate memory for creating V subsets
	int* parent = new int[graph->V * sizeof(int)];

	// Initialize all subsets as single element sets
	for(int i = 0; i < sizeof(int) * graph->V; i++) {
		parent[i] = i;
	}

	// Iterate through all edges of graph, find subset of
	// both vertices of every edge, if both subsets are
	// same, then there is cycle in graph.
	for (int i = 0; i < graph->E; ++i) {
		int x = find(parent, graph->edge[i].src);
		int y = find(parent, graph->edge[i].dest);

		if (x == y)
			return 1;

		Union(parent, x, y);
	}
	return 0;
}

// Driver code
int main()
{
	/* Let us create the following graph
		0
		| \
		| \
		1---2 */
	int V = 3, E = 3;
	Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;

	// add edge 1-2
	graph->edge[1].src = 1;
	graph->edge[1].dest = 2;

	// add edge 0-2
	graph->edge[2].src = 0;
	graph->edge[2].dest = 2;

	if (isCycle(graph))
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";

	return 0;
}

//Note that the implementation of union() and find() is naive 
//and takes O(n) time in the worst case. These methods 
//can be improved to O(logN) using Union by Rank or Height.