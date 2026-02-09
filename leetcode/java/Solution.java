class Solution {
    public boolean canPlaceFlowers(int[] flowerbed, int n){
        if(n==0){
            return true;
        }
        int count = 0;
        for (int i = 0; i < flowerbed.length; i++) {
           if(flowerbed[i]==0) {
            boolean isLeftZero = (i == 0 || flowerbed[i-1]==0);
            boolean isRightZero = (i==flowerbed.length-1 || flowerbed[i+1]==0);
            if(isLeftZero && isRightZero){
                flowerbed[i]=1;
                count++;
            }
           }
        }
        return count >= n;
    }
}