"""
1161. Maximum Level Sum of a Binary Tree
https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

Given the root of a binary tree, the level of its root is 1, the level of
its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at
level x is maximal.

Example 1:
    Input:  root = [1,7,0,7,-8,null,null]
    Output: 2
    Explanation: Level 1 sum = 1.
    Level 2 sum = 7 + 0 = 7.
    Level 3 sum = 7 + -8 = -1.
    So we return the level with the maximum sum which is level 2.

Example 2:
    Input:  root = [989,null,10250,98693,-89388,null,null,null,-32127]
    Output: 2

Constraints:
    - The number of nodes in the tree is in the range [1, 10^4].
    - -10^5 <= Node.val <= 10^5
"""
from typing import Optional
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        maxi, maxi_level, current_level = -float('inf'), 0, 0
        queue = deque()
        queue.append(root)
        while queue:
            current_sum = 0
            current_level+=1
            for _ in range(len(queue)):
                node = queue.popleft()
                current_sum += node.val
                if node.left is not None:
                    queue.append(node.left)
                if node.right is not None:
                    queue.append(node.right)
            if current_sum > maxi:
                maxi_level = current_level
                maxi = current_sum
        return maxi_level
            