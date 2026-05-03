import java.util.ArrayList;
import java.util.List;

public class BinaryTreeInorderTraversal {

    public void recurse(TreeNode root, List<Integer> nodes){
        if(root == null) return;
        recurse(root.left, nodes);
        nodes.add(root.val);
        recurse(root.right, nodes);
    }
    public List<Integer> inorderTraversal(TreeNode root){
        List<Integer> nodes = new ArrayList<>();
        recurse(root,nodes);
        return nodes;
    }
}