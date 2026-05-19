public class CountKthRootsinaRange {
    public int rootK(int n, int k) {
        int l = 0, r = n;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int powK = (int) Math.pow(mid, k);
            if (powK == n) {
                return mid;
            } else if (powK > n) {
                r = mid - 1;
            } else {
                ans = mid;
                l = mid + 1;
            }
        }
        return ans;
    }

    public int countKthRoots(int a, int b, int k) {
        int rootkOfA = rootK(a, k);
        int rootkOfB = rootK(b,k);
        return rootkOfB - rootkOfA;
    }
}