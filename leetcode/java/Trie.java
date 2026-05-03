class TrieNode {

    public boolean isEndOfWord;
    TrieNode[] nodes;
    TrieNode(){
        isEndOfWord = false;
        nodes = new TrieNode[26];
    }
    public int longestPrefix(){
        if(isEndOfWord == true){
            return 1;
        }
        int maxLength = 0;
        for(int i = 0; i < 26; i++){
            if(nodes[i]!=null){
                maxLength = Math.max(maxLength,1 + nodes[i].longestPrefix());
            }
        }
        return maxLength;
    }
}

public class Trie{

    TrieNode root;
    Trie(){
        root = new TrieNode();
    }
    public void addWord(String word){
        TrieNode node = root;
        for(char c : word.toCharArray()){
            int idx = c - 'a';
            if(node.nodes[idx]==null){
                node.nodes[idx] = new TrieNode();
            }
            node = node.nodes[idx];
        }
        node.isEndOfWord = true;
    }

    public int longestPrefix(){
        if(root == null) return 0;
        int maxLength = 0;
        for(int i = 0; i < 26; i++){
            if(root.nodes[i] != null){
                maxLength = Math.max(maxLength, root.nodes[i].longestPrefix());
            }
        }
        return maxLength;
    }

    public static void main(String[] args) {
        String[] strs = {"bat", "bag", "bank", "band"};
    }

}
