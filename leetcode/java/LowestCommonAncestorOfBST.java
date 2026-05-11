public class LowestCommonAncestorOfBST {
    TreeNode findLCA(TreeNode root, TreeNode p, TreeNode q){
        if(root == null) return null;
        if(p == null || q == null) return null;
        int maxi = Math.max(p.val,q.val);
        int mini = Math.min(p.val,q.val);
        if(root.val > maxi){
            return findLCA(root.left, p, q);
        }else if (root.val < mini){
            return findLCA(root.right,p,q);
        }
        return root;
    }
}
