import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
class Graph{
    private int V;
    List<Integer> adj[];
    Graph(int _V){
        this.V = _V;
        this.adj = new ArrayList[V];
        for(int i =0; i < V; i++){
            adj[i] = new ArrayList<Integer>();
        }
    }
    public void addEdge(int src, int dest){
        adj[src].add(dest);
    }
    public List<Integer> dfs(int v, boolean[] visited){
        List<Integer> nodes = new ArrayList<>();
        if(visited[v]!=false){
            return nodes;
        }
        nodes.add(v);
        visited[v] = true;
        for(int neighbor : this.adj[v]){
            nodes.addAll(dfs(neighbor,visited));
        }
        return nodes;
    }
    public List<Integer> topologicalSort(){
        int[] indegrees = new int[this.V];
        for(int i = 0; i < V; i++){
            for(var node : adj[i]){
                indegrees[node]++;
            }
        }
        List<Integer> answer = new ArrayList<>();
        Deque<Integer> nodesWithZeroIndegree = new ArrayDeque<>();
        for(int i = 0; i < V; i++){
            if(indegrees[i]==0){
                nodesWithZeroIndegree.offerFirst(i);
            }
        }
        while(nodesWithZeroIndegree.size()>0){

        }
        return answer;
    }
}