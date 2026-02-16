import java.util.*;
class Solution{
    public int reverseBits(int n){
        boolean[] bits = new boolean[32];
        for(int i = 0; i < 32; i++){
            if((n & (1<<i))!=0){
                bits[i]=true;
            }
        }
        //reversal
        int l = 0, r = 31;
        while(l<r){
            boolean temp = bits[l];
            bits[l] = bits[r];
            bits[r] = temp;
            l++;
            r--;
        }
        //convert to int
        int ans = 0;
        for(int i = 0; i < 32; i++){
            if(bits[i]){
                ans +=(1<<i);
            }
        }
        return ans;
    }
}