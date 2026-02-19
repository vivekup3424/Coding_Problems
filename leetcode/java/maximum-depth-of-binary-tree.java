class Solution{
    private int recurse(TreeNode root){
        if(root == null){
            return 0;
        }
        return Math.max(recurse(root.left),recurse(root.right)) + 1;
    }
    public int maxDepth(TreeNode root){
        return recurse(root);
    }
}