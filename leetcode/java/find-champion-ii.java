/*
 * 2924. Find Champion II
 * https://leetcode.com/problems/find-champion-ii/
 *
 * There are n teams numbered from 0 to n - 1 in a tournament, each team is
 * also a node in a DAG.
 *
 * You are given the integer n and a 0-indexed 2D integer array edges of
 * length m representing the DAG, where edges[i] = [ui, vi] indicates that
 * there is a directed edge from team ui to team vi in the graph.
 *
 * A directed edge from a to b in the graph means that team a is stronger
 * than team b and team b is weaker than team a.
 *
 * Team a will be the champion of the tournament if there is no team b
 * that is stronger than team a.
 *
 * Return the team that will be the champion of the tournament if there is
 * a unique champion, otherwise, return -1.
 *
 * Example 1:
 *   Input:  n = 3, edges = [[0,1],[1,2]]
 *   Output: 0
 *   Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team
 *   1. So the champion is team 0.
 *
 * Example 2:
 *   Input:  n = 4, edges = [[0,2],[1,3],[1,2]]
 *   Output: -1
 *   Explanation: Team 2 is weaker than team 0 and team 1. Team 3 is
 *   weaker than team 1. But team 1 and team 0 don't have a relationship.
 *
 * Constraints:
 *   - n == number of teams
 *   - 2 <= n <= 100
 *   - m == edges.length
 *   - 0 <= m <= n * (n - 1) / 2
 *   - edges[i].length == 2
 *   - 0 <= edges[i][j] <= n - 1
 *   - edges[i][0] != edges[i][1]
 *   - The input is generated such that if team a is stronger than team b,
 *     team b is not stronger than team a.
 *   - The input is generated such that if team a is stronger than team b
 *     and team b is stronger than team c, then team a is stronger than
 *     team c.
 */
class Solution {
    public int findChampion(int n, int[][] edges) {
        int[] indegree = new int[n];
        for(int i = 0; i < edges.length; i++){
            int[] edge = edges[i];
            indegree[edge[1]]++;
        }
        int countZeroIndegrees = 0;
        for(int i = 0; i < n; i++){
            if(indegree[i]==0)countZeroIndegrees++;
        }
        if(countZeroIndegrees > 1) return -1;
        for(int i = 0; i < n; i++){
            if(indegree[i]==0)return i;
        }
        return -1;
    }
}
