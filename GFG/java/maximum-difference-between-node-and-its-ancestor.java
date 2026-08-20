class Node{
    int data;
    Node left, right;
    Node(int item){
        data = item;
        left = right = null;
    }
}

class Solution{
    int recurse(Node node, int ancestorValue, int maxValue){
        if(node == null)return Integer.MIN_VALUE;
        int diff = ancestorValue - node.data;
        ancestorValue = Math.max(ancestorValue, node.data);
        
    }
    int maxDiff(Node root){
        int val = Integer.MIN_VALUE;
        
    }
}