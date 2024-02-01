class Solution
{
public:
    long long sum(int i, int j, int arr[], vector<vector<int>> &memo)
    {
        if (memo[i][j] != 0)
            return memo[i][j];
        if ((j - i) == 1)
            return memo[i][j] = max(arr[i], arr[j]);
        else
        {
            // choosing the ith element
            long long choice1 = arr[i] + min(sum(i + 2, j, arr, memo), sum(i + 1, j - 1, arr, memo));

            // choosing the jth element
            long long choice2 = arr[j] + min(sum(i + 1, j - 1, arr, memo), sum(i, j - 2, arr, memo));
            return memo[i][j] = max(choice1, choice2);
        }
    }
    long long maximumAmount(int arr[], int n)
    {
        vector<vector<int>> memo(n, vector<int>(n, 0));
        return sum(0, n - 1, arr, memo);
    }
};