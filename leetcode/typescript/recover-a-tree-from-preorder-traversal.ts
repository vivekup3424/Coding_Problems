import { ProgramUpdateLevel } from "typescript"

class TreeNode {
    val : number
    left: TreeNode | null
    right : TreeNode | null
    constructor(val ?: number, left ?: TreeNode, right ?: TreeNode) {
        this.val = (val===undefined) ? 0 : val
        this.left = (left===undefined)? null : left
        this.right = (right===undefined) ? null : right
    }
}
type NodeLevel = {
    node : TreeNode
    level : int
}
function recoverFromPreorder(traversal:string):TreeNode | null {
    let stack: Array<NodeLevel> = []
    let start = 0, n = traversal.length;
    while(start < n){
        let level = 0
        while(start < n && traversal[start] == '-'){
            level++;
        }
        
    }
}