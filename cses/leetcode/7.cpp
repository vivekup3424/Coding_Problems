
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int reverse(int x)
    {
        stack<int> s;
        int counter = 0, temp = 0;
        int curr = x;
        while (x)
        {
            temp = x % 10;
            x /= 10;
            s.push(temp);
        }
        int sum = 0;
        while (!s.empty())
        {

            temp = s.top();
            s.pop();
            if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && temp > 7))
                return 0;
            if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && temp < -8))
                return 0;
            sum += temp * pow(10, counter);
            counter++;
        }
        return sum;
    }
};
int main()
{
    int n = 123;
    Solution *A = new Solution();
    cout << A->reverse(n) << endl;
}