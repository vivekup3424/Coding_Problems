class Solution
{
public:
    int minPartitions(string n)
    {
        char m = '0';
        for (auto c : n)
        {
            m = max(m, c);
        }
        if (m == '9')
            break;
        return m - '0';
    }
};