import java.util.*;

class Solution {
    // Helper class to store a node and its color
    private static class Pair {
        int node;
        int color;
        
        Pair(int node, int color) {
            this.node = node;
            this.color = color;
        }
    }
    
    public boolean possibleBipartition(int n, int[][] dislikes) {
        // Create adjacency list representation of the graph
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        
        // Populate the graph with edges (dislike relationships)
        for (int[] edge : dislikes) {
            int u = edge[0];
            int v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);  // Undirected graph
        }
        
        // Array to track colors: -1 = uncolored, 0 = first group, 1 = second group
        int[] colors = new int[n + 1];
        Arrays.fill(colors, -1);
        
        // BFS to color the graph using Pair objects
        for (int i = 1; i <= n; i++) {
            // If this node is uncolored, start BFS from here
            if (colors[i] == -1) {
                Queue<Pair> queue = new LinkedList<>();
                queue.offer(new Pair(i, 0));  // Start with color 0
                colors[i] = 0;
                
                while (!queue.isEmpty()) {
                    Pair current = queue.poll();
                    int node = current.node;
                    int color = current.color;
                    
                    // Check all neighbors
                    for (int neighbor : graph.get(node)) {
                        if (colors[neighbor] == -1) {
                            // Assign the opposite color to the neighbor
                            int neighborColor = 1 - color;
                            colors[neighbor] = neighborColor;
                            queue.offer(new Pair(neighbor, neighborColor));
                        } else if (colors[neighbor] == color) {
                            // If neighbor has the same color, it's not bipartite
                            return false;
                        }
                    }
                }
            }
        }
        
        // If we can color all nodes without conflicts, it's bipartite
        return true;
    }
}