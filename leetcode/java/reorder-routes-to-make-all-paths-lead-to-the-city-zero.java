class Solution{
    public int minReorder(int n, int[][] connections){
        for(int i = 0; i < connections.length; i++){
            int first = connections[i][0];
            connections[i][0] = connections[i][1];
            connections[i][1] = first;
        }
        return 0;
    }
}