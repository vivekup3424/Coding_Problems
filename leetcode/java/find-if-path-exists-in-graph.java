import java.util.*;

class Solution{
    private boolean dfs(Map<Integer, List<Integer>> graph, Set<Integer> visited, int node, int destination){
        if(node==destination){
            return true;
        }
        visited.add(node);
        for(var neighbor: graph.getOrDefault(node, new ArrayList<>())){
            if(!visited.contains(neighbor)){
                if(dfs(graph,visited,neighbor,destination)){
                    return true;
                }
            }
        }
        return false;
    }
    public boolean validPath(int n, int[][]edges, int source, int desination){
        Map<Integer,List<Integer>> graph = new HashMap<>();
        for(var edge : edges){
            var u = edge[0];
            var v = edge[1];
            graph.computeIfAbsent(u, k->new ArrayList<>()).add(v);
            graph.computeIfAbsent(v, k->new ArrayList<>()).add(u);
        }
        Set<Integer> visited = new HashSet<Integer>();

        return dfs(graph, visited, source, desination);
    }
}