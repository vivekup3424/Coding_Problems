class Solution{
    public int maxArea(int[] height){
        int i = 0, j = height.length-1, maxi = Integer.MIN_VALUE;
        while(i<j){
            int current_area = Math.min(height[i],height[j]) * (j-i);
            maxi = Math.max(maxi,current_area);
            if(height[i]<height[j]){
                i++;
            }else{
                j--;
            }
        }
        return maxi;
    }
}