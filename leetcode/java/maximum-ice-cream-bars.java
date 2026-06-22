import java.util.*;
class Solution {
    public int maxIceCream(int[] costs, int coins) {
        Arrays.sort(costs);
        int count = 0;
        for(int i = 0; i < costs.length && coins >= costs[i]; i++){
            count++;
            coins -= costs[i];
        }
        return count;
    }
}