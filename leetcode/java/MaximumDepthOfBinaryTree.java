public class MaximumDepthOfBinaryTree {

    public int maxDepth(TreeNode root){
        //normal recursive approach
        if(root == null) return 0;
        return Math.max(maxDepth(root.left), maxDepth(root.right)) + 1;
    }
}