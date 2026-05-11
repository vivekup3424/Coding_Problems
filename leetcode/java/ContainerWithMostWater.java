public class ContainerWithMostWater {

    public int maxArea(int[] height){
        int n = height.length;
        int l = 0, r = n-1;
        int maxArea = 0;
        while(l<r){
            int area = Math.min(height[l],height[r]) * (r-l);
            maxArea = Math.max(maxArea,area);
            if(height[l]<height[r]) l++;
            else r--;
        }
        return maxArea;
    }
}