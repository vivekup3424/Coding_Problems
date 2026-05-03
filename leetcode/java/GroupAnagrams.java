import java.util.*;
public class GroupAnagrams {

    public List<List<String>> groupAnagrams(String[] strs){
        Map<String, List<String>> words = new HashMap<>();
        for(String str : strs){
            var temp = str.toCharArray();
            Arrays.sort(temp);
            var sortedStr = new String(temp);
            words.computeIfAbsent(
                sortedStr, 
                k -> new ArrayList<>()).add(str);
        }
        return new ArrayList<>(words.values());
    }
}