import java.util.PriorityQueue;

class Solution {
    public int[][] kClosest(int[][] points, int k) {
        int[][] answer = new int[k][];
        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a,b)->(a[2]-b[2]));
        for (int i = 0; i < points.length; i++) {
            int d = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            minHeap.add(new int[]{points[i][0], points[i][1], d});
        }
        for (int i = 0; i < k; i++) {
            var point = minHeap.poll();
            answer[i] = new int[]{point[0],point[1]};
        }
        return answer;
    }
}