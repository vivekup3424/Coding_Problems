import java.util.HashMap;
import java.util.Map;

class MinimumOperationstoTransformString {
    public int minOperations(String s){
        Map<Character, Integer> freqMap = new HashMap<>();
        for(char c : s.toCharArray()){
            if(freqMap.get(c)==null){
                freqMap.put(c, 1);
            }else{
                var currentFreq = freqMap.get(c);
                freqMap.put(c, currentFreq+1);
            }
        }
        for(var something : freqMap.entrySet()){

        }
        return -100;
    }
}