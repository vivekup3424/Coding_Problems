/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
package main

import "math"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func TotalWays(node, parent *TreeNode) int {
	sum := 0
	if node == nil {
		return sum
	}
	sum += int(math.Abs(float64(TotalWays(node.Left, node))))
	sum += int(math.Abs(float64(TotalWays(node.Right, node))))
	sum += int(math.Abs(float64(node.Val - 1)))
	return sum
}
func distributeCoins(root *TreeNode) int {
	return TotalWays(root, nil)
}
