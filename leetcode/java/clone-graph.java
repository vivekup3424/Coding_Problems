import java.util.*;
class Node{
    public int val;
    public List<Node> neighbors;
    public Node(){
        val = 0;
        neighbors = new ArrayList<>();
    }
    public Node(int _val){
        val = _val;
        neighbors = new ArrayList<>();
    }
}
class Solution{
    public Node cloneGraph(Node node){
        if(node == null) return null;
        Map<Node, Node> visited = new HashMap<>();
        Deque<Node> queue = new ArrayDeque<>();
        visited.put(node, new Node(node.val));
        queue.add(node);
        while(!queue.isEmpty()){
            Node curr = queue.poll();
            for(Node neighbor : curr.neighbors){
                if(!visited.containsKey(neighbor)){
                    visited.put(neighbor, new Node(neighbor.val));
                    queue.add(neighbor);
                }
                visited.get(curr).neighbors.add(visited.get(neighbor));
            }
        }
        return visited.get(node);
    }
}