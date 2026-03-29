import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution{
    static class Pair{
        long distance;
        int node;
        Pair(long distance, int node){
            this.distance = distance;
            this.node = node;
        }
    }
    public int countPaths(int n, int[][] edges){
        int MOD = (int)(1e9+7);
        //Adjacency List
        Map<Integer,List<Integer>> graph = new HashMap<>();
        for(int i = 0; i < n; i++) graph.put(0,new ArrayList<>());
        for(int[] edge: edges){
            graph.get(edge[0]).add(new int[]{})
        }

    }
}