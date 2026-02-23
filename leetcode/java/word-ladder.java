import java.util.*;
class Solution{
    public int ladderLength(String beginWord, String endWord, List<String> wordList){
        wordList.add(beginWord);
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
        //so the map has been constructed now
        System.out.print("Neighbors Map");
        System.out.println(neighbors);
        //let's do bfs now
        Queue<String> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();
        queue.add(beginWord);
        visited.add(beginWord);
        int distance = 1;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for(int i = 0; i < size; i++){
                String word = queue.poll();
                if(word.equals(endWord)){
                    return distance;
                }
                for(String neighbor: neighbors.getOrDefault(word, new ArrayList<>())){
                    if(!visited.contains(neighbor)){
                        visited.add(neighbor);
                        queue.add(neighbor);
                    }
                }
            }
            distance++;
        }
        return 0;
    }
    public static void main(String[] args) {
        Solution solution = new Solution();
        String beginWord = "hit", endWord = "cog";
        List<String> wordList = new ArrayList<>(Arrays.asList("hot", "dog", "lot", "dot", "log", "cog"));
        System.out.println(solution.ladderLength(beginWord, endWord, wordList));
    }
}