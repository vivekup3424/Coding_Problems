class Solution
{
public:
    string countAndSay(int n)
    {
        if (n == 1)
            return "1";
        if (n == 2)
            return "11";

        string prev = "11";

        for (int i = 3; i <= n; i++)
        {
            string next = "";
            int count = 1;

            for (int j = 1; j < prev.size(); j++)
            {
                if (prev[j] == prev[j - 1])
                {
                    count++;
                }
                else
                {
                    next += to_string(count) + prev[j - 1];
                    count = 1;
                }
            }

            next += to_string(count) + prev.back();
            prev = next;
        }

        return prev;
    }
};
