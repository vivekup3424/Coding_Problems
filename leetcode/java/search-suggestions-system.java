class TrieNode{
    private TrieNode[] nodes;
    private boolean isEndofWord;
    private int wordCount;
    TrieNode(){
        this.nodes = new TrieNode[26];
        this.wordCount = 0;
        this.isEndofWord = false;
    }
    public void insertWord(String word){
        for(int i = 0; i < word.length(); i++){
            int idx = word.charAt(i) - 'a';
            if(this.nodes[idx] == null){
                this.nodes[idx] = new TrieNode();
            }
        }
    }
}