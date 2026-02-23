import java.util.*;
class Solution{
    public int ladderLength(String beginWord, String endWord, List<String> wordList){
        return 0;
    }
    public static void main(String[] args) {
        Solution solution = new Solution();
        String beginWord = "hit", endWord = "cog";
        List<String> wordList = new ArrayList<>(Arrays.asList("hot", "dog", "lot", "dot", "log", "cog"));
        System.out.println(solution.ladderLength(beginWord, endWord, wordList));
    }
}