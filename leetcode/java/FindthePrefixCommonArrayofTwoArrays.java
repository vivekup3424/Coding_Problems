import java.util.HashSet;
import java.util.Set;

public class FindthePrefixCommonArrayofTwoArrays {

    public int[] findThePrefixCommonArray(int[] A, int[] B){
        int n = A.length;
        int[] answer = new int[n];
        Set<Integer> st = new HashSet<>();
        for(int i = n-1; i >= 0; i--){
            answer[i] = n - st.size();
            st.add(A[i]);
            st.add(B[i]);
        }
        return answer;
    }
}