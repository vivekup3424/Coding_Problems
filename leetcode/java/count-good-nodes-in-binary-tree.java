class Solution{
    public int countGoodNodes(TreeNode root){
        if(root==null){
            return 0;
        }
        return recurse(root.left, root.val) +
        recurse(root.right, root.val);
    }
}