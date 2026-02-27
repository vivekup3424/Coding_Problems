import java.util.ArrayList;
import java.util.Collections;

class Something {

    static ArrayList<ArrayList<Integer>> createGraph(int V, int[][] edges) {
        ArrayList<ArrayList<Integer>> mat = new ArrayList<>();

        // Initialize the matrix with 0
        for (int i = 0; i < V; i++) {
            ArrayList<Integer> row = new ArrayList<>(Collections.nCopies(V, 0));
            mat.add(row);
        }

        // Add each edge to the adjacency matrix
        for (int[] it : edges) {
            int u = it[0];
            int v = it[1];
            mat.get(u).set(v, 1);
            
             // since the graph is undirected
            mat.get(v).set(u, 1); 
        }
        return mat;
    }

    public static void main(String[] args) {
        int V = 3;

        // List of edges (u, v)
        int[][] edges = {
            {0, 1},
            {0, 2},
            {1, 2}
        };

        // Build the graph using edges
        ArrayList<ArrayList<Integer>> mat = createGraph(V, edges);

        System.out.println("Adjacency Matrix Representation:");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                System.out.print(mat.get(i).get(j) + " ");
            System.out.println();
        }
    }
}