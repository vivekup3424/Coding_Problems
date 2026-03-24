import java.util.*;

class Solution {
    public boolean canFinish(int n, int[][] prerequisites) {
        int[] indegree = new int[n];
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());

        for (int[] edge : prerequisites) {
            int x = edge[0], y = edge[1]; // y -> x (y must come before x)
            graph.get(y).add(x);
            indegree[x]++;
        }

        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) queue.offer(i);
        }

        int processed = 0;
        while (!queue.isEmpty()) {
            int node = queue.poll();
            processed++;
            for (int neighbor : graph.get(node)) {
                if (--indegree[neighbor] == 0) queue.offer(neighbor);
            }
        }

        return processed == n;
    }
}