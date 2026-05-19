import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class GFG {
    public static int minSteps(int[] arr, int start,
                               int end)
    {
        int mod = 1000;
        int[] dist = new int[mod];
        Arrays.fill(dist, -1);
        Queue<Integer> q = new LinkedList<>();
        start = start % mod;
        end = end % mod;
        q.add(start);
        dist[start] = 0;
        while (!q.isEmpty()) {
            int curr = q.poll();
            if (curr == end) {
                return dist[curr];
            }
            for (int i = 0; i < arr.length; i++) {
                int next = (curr * arr[i]) % mod;
                if (dist[next] == -1) {
                    dist[next] = dist[curr] + 1;
                    q.add(next);
                }
            }
        }
        return -1;
    }
}