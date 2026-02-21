import java.util.*;
class Solution{
    public int ladderLength(String beginWord, String endWord, List<String> wordList){
        int count = 0;
        Map<String, List<String>> neighbors = new HashMap<>();
        for (int i = 0; i < wordList.size(); i++) {
           for (int j = i + 1; j < wordList.size(); j++) {
            int diff = 0;
            for(int k = 0; k < wordList.get(i).length(); k++){
                if(wordList.get(i).charAt(k) != wordList.get(j).charAt(k)){
                    diff++;
                }
                if(diff > 1) break;
            }
            if(diff == 1){
                neighbors.computeIfAbsent(wordList.get(i), x -> new ArrayList<>()).add(wordList.get(j));
                neighbors.computeIfAbsent(wordList.get(j), x -> new ArrayList<>()).add(wordList.get(i));
            }
           }
        }


        return count;
    }
}