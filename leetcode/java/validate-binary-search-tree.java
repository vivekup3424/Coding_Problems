public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode() {
    };

    TreeNode(int _val) {
        this.val = _val;
    }

    TreeNode(int _val, TreeNode _left, TreeNode _right) {
        this.val = _val;
        this.left = _left;
        this.right = _right;
    }
}

class Solution {
    private boolean validateNode(TreeNode node, int lower_bound, int upper_bound) {
        if (node == null) {
            return true;
        } else if ((node.val > lower_bound && node.val < upper_bound) == false) {
            return false;
        } else {
            return (validateNode(node.left, lower_bound, node.val)
                    && validateNode(node.right, node.val, upper_bound));
        }
    }

    public boolean isValidBST(TreeNode root) {
        int lower_bound = Integer.MIN_VALUE;
        int upper_bound = Integer.MAX_VALUE;
        return validateNode(root, lower_bound, upper_bound);
    }
}