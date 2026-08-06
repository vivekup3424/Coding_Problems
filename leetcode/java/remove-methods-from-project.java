/*
 * 3310. Remove Methods From Project
 * https://leetcode.com/problems/remove-methods-from-project/
 *
 * You maintain a project with n methods numbered 0 to n - 1. Given n, k,
 * and a 2D array invocations where invocations[i] = [ai, bi] indicates
 * method ai invokes method bi.
 *
 * Method k has a bug. Method k and any methods it invokes directly or
 * indirectly are considered "suspicious" and should be removed.
 *
 * Methods can only be removed if no method outside the removal group
 * invokes any methods within it.
 *
 * Return an array of all remaining methods. If it's impossible to remove
 * all suspicious methods, none should be removed.
 *
 * Example 1:
 *   Input:  n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
 *   Output: [0,1,2,3]
 *   Explanation: Methods 1 and 2 are suspicious but are invoked by
 *                non-suspicious methods 0 and 3, so nothing can be
 *                removed.
 *
 * Example 2:
 *   Input:  n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
 *   Output: [3,4]
 *   Explanation: Methods 0, 1, and 2 are suspicious and not invoked by
 *                any other method, so they can be removed.
 *
 * Example 3:
 *   Input:  n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
 *   Output: []
 *   Explanation: All methods are suspicious and can be removed.
 *
 * Constraints:
 *   - 1 <= n <= 10^5
 *   - 0 <= k <= n - 1
 *   - 0 <= invocations.length <= 2 * 10^5
 *   - invocations[i] == [ai, bi]
 *   - 0 <= ai, bi <= n - 1
 *   - ai != bi
 *   - All invocation pairs are unique
 */
import java.util.*;
class Solution {
    public List<Integer> remainingMethods(int n, int k, int[][] invocations) {
        //invocations is like a list of directed edges
        //creating adjacency matrix
        Map<Integer, List<Integer>> graph = new HashMap<>();
        int[] indegrees = new int[n];
        for(int[] edge : invocations){
            int u = edge[0], v = edge[1];
            graph.computeIfAbsent(u, key -> new ArrayList<>()).add(v);
            indegrees[v]++;
        }
        //drain indegrees starting from k; a node only clears once every
        //predecessor of it has cleared first
        boolean[] removed = new boolean[n];
        Queue<Integer> q = new ArrayDeque<>();
        q.add(k);
        removed[k] = true;
        int removedCount = 1;
        while(q.size()>0){
            int node = q.poll();
            for(int neighbor : graph.getOrDefault(node, Collections.emptyList())){
                indegrees[neighbor]--;
                if(indegrees[neighbor]==0 && !removed[neighbor]){
                    removed[neighbor] = true;
                    removedCount++;
                    q.add(neighbor);
                }
            }
        }

        //the true suspicious set: everything reachable from k, ignoring indegree
        boolean[] suspicious = new boolean[n];
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(k);
        suspicious[k] = true;
        int suspiciousCount = 1;
        while(!stack.isEmpty()){
            int node = stack.pop();
            for(int neighbor : graph.getOrDefault(node, Collections.emptyList())){
                if(!suspicious[neighbor]){
                    suspicious[neighbor] = true;
                    suspiciousCount++;
                    stack.push(neighbor);
                }
            }
        }

        //removed is only a subset of suspicious; they're equal iff nothing
        //outside the suspicious set invokes into it, so the whole group can go
        boolean canRemoveAll = removedCount == suspiciousCount;
        List<Integer> result = new ArrayList<>();
        for(int i = 0; i < n; i++){
            if(!canRemoveAll || !removed[i]){
                result.add(i);
            }
        }
        return result;
    }
}
