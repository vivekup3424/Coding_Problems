class SumOfKDigitNumbers {
    static final long MOD = 1_000_000_007;

    public int sumOfNumbers(int l, int r, int k) {
        long n = r - l + 1;
        long digitSum = n * (l + r) / 2;

        long nPowK1 = modPow(n, k - 1, MOD);
        long temp = (modPow(10, k, MOD) - 1 + MOD) % MOD;
        long inv9 = modPow(9, MOD - 2, MOD);

        long ans = digitSum % MOD;
        ans = ans * nPowK1 % MOD;
        ans = ans * temp % MOD;
        ans = ans * inv9 % MOD;

        return (int) ans;
    }

    private long modPow(long base, long exp, long mod) {
        base %= mod;
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }

    public static void main(String[] args) {
        SumOfKDigitNumbers sol = new SumOfKDigitNumbers();
        System.out.println(sol.sumOfNumbers(1, 2, 2));    // 66
        System.out.println(sol.sumOfNumbers(0, 1, 3));    // 444
        System.out.println(sol.sumOfNumbers(5, 5, 10));   // 555555520
    }
}
