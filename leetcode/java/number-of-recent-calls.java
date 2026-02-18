import java.util.ArrayDeque;
import java.util.Queue;

class RecentCounter{
    private Queue<Integer> queue;
    private final int maxWindowMs = 3000;
    public RecentCounter(){
        queue = new ArrayDeque<>();
    }
    public int ping(int t){
        while(!queue.isEmpty() && t - queue.peek() > maxWindowMs){
            queue.poll();
        }
        queue.add(t);
        return queue.size();
    }
    public static void main(String[] args){
        RecentCounter recentCounter = new RecentCounter();
        //writing down a series of operations
        int[] pingTimes = {1,100,3001,3002,3030,4000,4001,4002,4003,5000};
        for(int time : pingTimes){
            int numberOfRequests = recentCounter.ping(time);
            System.out.printf("time = %d, numer of requests = %d\n", time, numberOfRequests);
        }
    }

}