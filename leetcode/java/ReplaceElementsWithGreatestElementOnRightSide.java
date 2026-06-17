public class ReplaceElementsWithGreatestElementOnRightSide {
    public int[] replaceElements(int[] arr) {
        int n = arr.length;
        int[] ans = new int[n];
        int maxi = -1;
        for (int i = n - 1; i >= 0; i--) {
            ans[i] = maxi;
            maxi = Math.max(maxi, arr[i]);
        }
        return ans;
    }
}