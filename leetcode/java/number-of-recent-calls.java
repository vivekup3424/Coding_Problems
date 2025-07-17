import java.util.*;

class RecentCounter{
    private Queue<Integer> request;
    public RecentCounter(){
        this.request = new ArrayDeque<>();
    }

    public int ping(int t){
        request.add(t);
        while(request.peek()!=null && (t - request.peek()) > 3000){
            request.poll();
        }
        return request.size();
    }
}