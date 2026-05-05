public class BinarySearchTree {

    // ── Node ───────────────────────────────────────────────────────────────
    static class Node {
        int val;
        Node left, right;

        Node(int val) {
            this.val = val;
        }
    }

    // ── Tree ───────────────────────────────────────────────────────────────
    private Node root;

    // ── Insert ─────────────────────────────────────────────────────────────
    public void insert(int val) {
        root = insertRec(root, val);
    }

    private Node insertRec(Node node, int val) {
        if (node == null)
            return new Node(val); // base case: empty spot found

        if (val < node.val)
            node.left = insertRec(node.left, val);
        else if (val > node.val)
            node.right = insertRec(node.right, val);
        // duplicate values are ignored

        return node;
    }

    // ── Search ─────────────────────────────────────────────────────────────
    public boolean search(int val) {
        return searchRec(root, val);
    }

    private boolean searchRec(Node node, int val) {
        if (node == null)
            return false;
        if (val == node.val)
            return true;
        if (val < node.val)
            return searchRec(node.left, val);
        return searchRec(node.right, val);
    }

    // ── Delete ─────────────────────────────────────────────────────────────
    public void delete(int val) {
        root = deleteRec(root, val);
    }

    private Node deleteRec(Node node, int val) {
        if (node == null)
            return null;

        if (val < node.val) {
            node.left = deleteRec(node.left, val);
        } else if (val > node.val) {
            node.right = deleteRec(node.right, val);
        } else {
            // ── Found the node to delete ───────────────────────────────────

            // Case 1 & 2: 0 or 1 child
            if (node.left == null)
                return node.right;
            if (node.right == null)
                return node.left;

            // Case 3: 2 children
            // Replace value with in-order successor (smallest in right subtree)
            node.val = minValue(node.right);
            // Then delete that successor from the right subtree
            node.right = deleteRec(node.right, node.val);
        }

        return node;
    }

    // helper: find smallest value in a subtree
    private int minValue(Node node) {
        while (node.left != null)
            node = node.left;
        return node.val;
    }

    // ── Traversals ─────────────────────────────────────────────────────────

    // Left → Root → Right (produces sorted output)
    public void inOrder() {
        System.out.print("In-order:    ");
        inOrderRec(root);
        System.out.println();
    }

    private void inOrderRec(Node node) {
        if (node == null)
            return;
        inOrderRec(node.left);
        System.out.print(node.val + " ");
        inOrderRec(node.right);
    }

    // Root → Left → Right
    public void preOrder() {
        System.out.print("Pre-order:   ");
        preOrderRec(root);
        System.out.println();
    }

    private void preOrderRec(Node node) {
        if (node == null)
            return;
        System.out.print(node.val + " ");
        preOrderRec(node.left);
        preOrderRec(node.right);
    }

    // Left → Right → Root
    public void postOrder() {
        System.out.print("Post-order:  ");
        postOrderRec(root);
        System.out.println();
    }

    private void postOrderRec(Node node) {
        if (node == null)
            return;
        postOrderRec(node.left);
        postOrderRec(node.right);
        System.out.print(node.val + " ");
    }

    // ── Height ─────────────────────────────────────────────────────────────
    public int height() {
        return heightRec(root);
    }

    private int heightRec(Node node) {
        if (node == null)
            return 0;
        return 1 + Math.max(heightRec(node.left), heightRec(node.right));
    }

    // ── Main ───────────────────────────────────────────────────────────────
    public static void main(String[] args) {
        BinarySearchTree bst = new BinarySearchTree();

        int[] values = { 50, 30, 70, 20, 40, 60, 80 };
        for (int v : values)
            bst.insert(v);

        // Traversals
        bst.inOrder(); // 20 30 40 50 60 70 80
        bst.preOrder(); // 50 30 20 40 70 60 80
        bst.postOrder(); // 20 40 30 60 80 70 50

        System.out.println("Height:      " + bst.height()); // 3

        // Search
        System.out.println("Search 40:   " + bst.search(40)); // true
        System.out.println("Search 99:   " + bst.search(99)); // false

        // Delete
        bst.delete(30); // node with 2 children
        bst.inOrder(); // 20 40 50 60 70 80

        bst.delete(20); // leaf node
        bst.inOrder(); // 40 50 60 70 80
    }
}

public class BinarySearchTree {

    // ── Node ───────────────────────────────────────────────────────────────
    static class Node {
        int val;
        Node left, right;

        Node(int val) {
            this.val = val;
        }
    }

    // ── Tree ───────────────────────────────────────────────────────────────
    private Node root;

    // ── Insert ─────────────────────────────────────────────────────────────
    public void insert(int val) {
        root = insertRec(root, val);
    }

    private Node insertRec(Node node, int val) {
        if (node == null)
            return new Node(val); // base case: empty spot found

        if (val < node.val)
            node.left = insertRec(node.left, val);
        else if (val > node.val)
            node.right = insertRec(node.right, val);
        // duplicate values are ignored

        return node;
    }

    // ── Search ─────────────────────────────────────────────────────────────
    public boolean search(int val) {
        return searchRec(root, val);
    }

    private boolean searchRec(Node node, int val) {
        if (node == null)
            return false;
        if (val == node.val)
            return true;
        if (val < node.val)
            return searchRec(node.left, val);
        return searchRec(node.right, val);
    }

    // ── Delete ─────────────────────────────────────────────────────────────
    public void delete(int val) {
        root = deleteRec(root, val);
    }

    private Node deleteRec(Node node, int val) {
        if (node == null)
            return null;

        if (val < node.val) {
            node.left = deleteRec(node.left, val);
        } else if (val > node.val) {
            node.right = deleteRec(node.right, val);
        } else {
            // ── Found the node to delete ───────────────────────────────────

            // Case 1 & 2: 0 or 1 child
            if (node.left == null)
                return node.right;
            if (node.right == null)
                return node.left;

            // Case 3: 2 children
            // Replace value with in-order successor (smallest in right subtree)
            node.val = minValue(node.right);
            // Then delete that successor from the right subtree
            node.right = deleteRec(node.right, node.val);
        }

        return node;
    }

    // helper: find smallest value in a subtree
    private int minValue(Node node) {
        while (node.left != null)
            node = node.left;
        return node.val;
    }

    // ── Traversals ─────────────────────────────────────────────────────────

    // Left → Root → Right (produces sorted output)
    public void inOrder() {
        System.out.print("In-order:    ");
        inOrderRec(root);
        System.out.println();
    }

    private void inOrderRec(Node node) {
        if (node == null)
            return;
        inOrderRec(node.left);
        System.out.print(node.val + " ");
        inOrderRec(node.right);
    }

    // Root → Left → Right
    public void preOrder() {
        System.out.print("Pre-order:   ");
        preOrderRec(root);
        System.out.println();
    }

    private void preOrderRec(Node node) {
        if (node == null)
            return;
        System.out.print(node.val + " ");
        preOrderRec(node.left);
        preOrderRec(node.right);
    }

    // Left → Right → Root
    public void postOrder() {
        System.out.print("Post-order:  ");
        postOrderRec(root);
        System.out.println();
    }

    private void postOrderRec(Node node) {
        if (node == null)
            return;
        postOrderRec(node.left);
        postOrderRec(node.right);
        System.out.print(node.val + " ");
    }

    // ── Height ─────────────────────────────────────────────────────────────
    public int height() {
        return heightRec(root);
    }

    private int heightRec(Node node) {
        if (node == null)
            return 0;
        return 1 + Math.max(heightRec(node.left), heightRec(node.right));
    }

    // ── Main ───────────────────────────────────────────────────────────────
    public static void main(String[] args) {
        BinarySearchTree bst = new BinarySearchTree();

        int[] values = { 50, 30, 70, 20, 40, 60, 80 };
        for (int v : values)
            bst.insert(v);

        // Traversals
        bst.inOrder(); // 20 30 40 50 60 70 80
        bst.preOrder(); // 50 30 20 40 70 60 80
        bst.postOrder(); // 20 40 30 60 80 70 50

        System.out.println("Height:      " + bst.height()); // 3

        // Search
        System.out.println("Search 40:   " + bst.search(40)); // true
        System.out.println("Search 99:   " + bst.search(99)); // false

        // Delete
        bst.delete(30); // node with 2 children
        bst.inOrder(); // 20 40 50 60 70 80

        bst.delete(20); // leaf node
        bst.inOrder(); // 40 50 60 70 80
    }
}