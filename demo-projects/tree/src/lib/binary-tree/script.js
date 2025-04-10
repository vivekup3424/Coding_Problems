class TreeNode {
    constructor(value) {
        this.value = value;
        this.left = null;
        this.right = null;
        this.x = 0;
        this.y = 0;
    }
}

class BinaryTree {
    constructor() {
        this.root = null;
        this.nodeCount = 0;
        this.levelHeight = 100;
        this.horizontalSpacing = 100;
    }

    addNode(value) {
        const newNode = new TreeNode(value);
        if (!this.root) {
            this.root = newNode;
            this.root.x = window.innerWidth / 2;
            this.root.y = 50;
        } else {
            this._insertNode(this.root, newNode);
        }
        this.nodeCount++;
        this._updatePositions(this.root, this.root.x, this.root.y, 0);
        this.render();
    }

    _insertNode(node, newNode) {
        if (newNode.value < node.value) {
            if (node.left === null) {
                node.left = newNode;
            } else {
                this._insertNode(node.left, newNode);
            }
        } else {
            if (node.right === null) {
                node.right = newNode;
            } else {
                this._insertNode(node.right, newNode);
            }
        }
    }

    _updatePositions(node, x, y, level) {
        if (!node) return;

        node.x = x;
        node.y = y;

        const horizontalOffset = this.horizontalSpacing / Math.pow(2, level);
        
        if (node.left) {
            this._updatePositions(node.left, x - horizontalOffset, y + this.levelHeight, level + 1);
        }
        if (node.right) {
            this._updatePositions(node.right, x + horizontalOffset, y + this.levelHeight, level + 1);
        }
    }

    render() {
        const container = document.getElementById('tree-container');
        container.innerHTML = '';
        
        if (!this.root) return;

        this._renderNode(this.root, container);
    }

    _renderNode(node, container) {
        if (!node) return;

        const nodeElement = document.createElement('div');
        nodeElement.className = 'node';
        nodeElement.textContent = node.value;
        nodeElement.style.left = `${node.x - 25}px`;
        nodeElement.style.top = `${node.y - 25}px`;
        container.appendChild(nodeElement);

        if (node.left) {
            this._createConnection(node, node.left, container);
            this._renderNode(node.left, container);
        }
        if (node.right) {
            this._createConnection(node, node.right, container);
            this._renderNode(node.right, container);
        }
    }

    _createConnection(parent, child, container) {
        const connection = document.createElement('div');
        connection.className = 'connection';
        
        const length = Math.sqrt(
            Math.pow(child.x - parent.x, 2) + 
            Math.pow(child.y - parent.y, 2)
        );
        
        const angle = Math.atan2(child.y - parent.y, child.x - parent.x);
        
        connection.style.width = `${length}px`;
        connection.style.left = `${parent.x}px`;
        connection.style.top = `${parent.y}px`;
        connection.style.transform = `rotate(${angle}rad)`;
        
        container.appendChild(connection);
    }

    clear() {
        this.root = null;
        this.nodeCount = 0;
        this.render();
    }
}

// Initialize the binary tree
const tree = new BinaryTree();

// Event listeners
document.getElementById('addNode').addEventListener('click', () => {
    const value = Math.floor(Math.random() * 100);
    tree.addNode(value);
});

document.getElementById('clearTree').addEventListener('click', () => {
    tree.clear();
}); 