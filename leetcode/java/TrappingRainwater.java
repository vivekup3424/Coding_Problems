class TrappingRainwater {
    public int trap(int[] height) {
        int n = height.length;
        var prefixMax = new int[n];
        var suffixMax = new int[n];
        for (int i = 0; i < n; i++) {
            if (i == 0) {
               prefixMax[i] = height[i];
            }else{
                Stir
                prefixMax[i] = Math.max(prefixMax[i-1], height[i]);
            }
        }
        for(int i = n-1; i >= 0; i--){
            if(i==n-1){
                suffixMax[i] = height[i];
            }else{
                suffixMax[i] = Math.max(suffixMax[i], )
            }
        }
    }
}