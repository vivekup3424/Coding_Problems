import java.util.*;
class Solution{
    public int[] sumOfDistancesInTree(int n, int[][] edges){
        //construct a graph
        Map<Integer, List<Integer>> graph = new HashMap<>();
        for(var edge : edges){
            int u = edge[0], v = edge[1];
            graph.computeIfAbsent(u, k->new ArrayList<>()).add(v);
            graph.computeIfAbsent(v, k->new ArrayList<>()).add(u);
        }
        
    }
}