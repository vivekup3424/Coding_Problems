//0 index = 'a'
//25 index = 'z'
class TrieNode{
    boolean isEndOfWord;
    TrieNode[] children;
    TrieNode(){
        isEndOfWord = false;
        children = new TrieNode[26];
    }
}
public class Trie {

    private TrieNode root;
    Trie(){
        root = new TrieNode();
    }
    void addWord(String word){
        TrieNode temp = root;
        for(int i = 0; i < word.length(); i++){
            int idx = word.charAt(i) - 'a';
            if(temp.children[idx]==null) temp.children[idxN] = new TrieNode();
            temp = temp.children[idx];
        }
        temp.isEndOfWord = true;
    }
}