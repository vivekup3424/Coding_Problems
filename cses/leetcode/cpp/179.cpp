
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    static bool compare(const string &a, const string &b)
    {
        return a + b > b + a;
    }
    string largestNumber(vector<int> &nums)
    {
        vector<string> numbers;
        for (auto n : nums)
        {
            numbers.push_back(to_string(n));
        }
        sort(numbers.begin(), numbers.end(), compare);
        string result = "";
        for (auto n : numbers)
        {
            result += n;
        }
        // trim leading zeros from result
        int i = 0;
        while (i + 1 < result.size() && result[i] == '0')
        {
            i++;
        }
        return result.substr(i);
    }
};
int main()
{
    ;
}