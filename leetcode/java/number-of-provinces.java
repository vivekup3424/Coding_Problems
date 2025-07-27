class DSU{
    int[] parent;
    int[] size;
    DSU(int n){
        parent = new int[n];
        size = new int[n];
        for(int i = 0;i < n;i++){
            parent[i] = i;
            size[i] = 1;
        }
    }
    int findParent(int x){
        if(parent[x] != x){
            parent[x] = findParent(parent[x]);
        }
        return parent[x];
    }
    void union(int x, int y){
        int parentX = findParent(x);
        int parentY = findParent(y);
        if(parentX == parentY) return;
        int sizeX = size[parentX];
        int sizeY = size[parentY];
        if(sizeX < sizeY){
            parent[parentX] = parentY;
            size[parentY] += sizeX;
        }
        else{
            parent[parentY] = parentX;
            size[parentX] += sizeY;
        }
    }
    int getComponentCount(){
        int count = 0;
        for(int i = 0;i < parent.length;i++){
            if(parent[i] == i) count++;
        }
        return count;
    }
}
class Solution {
    public int findCircleNum(int[][] isConnected){
        int n = isConnected.length;
        DSU dsu = new DSU(n);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(isConnected[i][j] == 1){
                    dsu.union(i, j);
                }
            }
        }
        return dsu.getComponentCount();
    }
}