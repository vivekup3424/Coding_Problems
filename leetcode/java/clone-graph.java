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
    }
}
class 