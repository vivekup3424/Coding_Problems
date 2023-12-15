int largestAltitude(vector<int> &gain)
{
    int n = gain.size();
    int max = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += gain[i];
        if (sum > max)
        {
            max = sum;
        }
    }
    return max;
};