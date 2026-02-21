import java.util.*;

class Solution{
    public int hIndex(int[] citations){
        int answer = -1;
        int l = 0, r = citations.length-1, n = citations.length;
        Arrays.sort(citations);
        while (l<r) {
            int mid = (l+r)/2;
            if((n-mid) >= citations[mid]){
                answer = mid;
                r = mid + 1;
            }else{
                l = mid - 1;
            }
        }
        return answer;
    }
}