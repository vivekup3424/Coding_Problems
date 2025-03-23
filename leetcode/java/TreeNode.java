public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}
class Solution {
    public int maxDepth(TreeNode root) {
        var maxdepth = 0;
        depthFirstSearch(root, 0, maxdepth);
        return maxdepth;
        int ma
    }
    public void depthFirstSearch(TreeNode root,int currentDepth, int maxDepth){
        return 0;
    }
}
