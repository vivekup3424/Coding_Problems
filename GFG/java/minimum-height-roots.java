import java.util.*;
class Solution{
    public ArrayList<Integer> minHeightRoot(int V, int[][] edges){
        Map<Integer, Set<Integer>> graph = new HashMap<>();
        int[] degree = new int[V];
        for(int[] edge : edges){
            int u = edge[0], v = edge[1];
            graph.computeIfAbsent(u, k -> new HashSet<>()).add(v);
            graph.computeIfAbsent(v, k -> new HashSet<>()).add(u);
            degree[u]++;
            degree[v]++;
        }

        int countOfNodes = V;
        Queue<Integer> leafNodes = new ArrayDeque<>();
        for(int i = 0; i < countOfNodes; i++){
            if(degree[i]==1){
                leafNodes.add(i);
            }
        }

        while(countOfNodes > 2){
            int leafCount = leafNodes.size();
            countOfNodes -= leafCount;
            for(int i = 0; i < leafCount; i++){
                int leaf = leafNodes.poll();
                for(int neighbor : graph.get(leaf)){
                    degree[neighbor]--;
                    if(degree[neighbor] == 1){
                        leafNodes.add(neighbor);
                    }
                }
            }
        }

        return new ArrayList<>(leafNodes);
    }
}