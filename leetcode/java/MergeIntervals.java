import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MergeIntervals{
    public int[][] merge(int[][] intervals){
        //ascending order of first element
        Arrays.sort(intervals, (i,j)-> i[0]-j[0]);
        List<int[]> answer = new ArrayList<>();
        for(int[] interval : intervals){
            if(answer.isEmpty() || answer.getLast()[1] < interval[0]){
                answer.add(interval);
            }else{
                answer.getLast()[1] = Math.max(answer.getLast()[1], interval[1]);
            }
        }
        return answer.toArray(new int[answer.size()][]);
    }
}
