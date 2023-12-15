
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool areSameSigns(int a, int b)
    {
        return (a + b) == (abs(a) + abs(b));
    }
    int maxMagnitudeNumber(int a, int b)
    {
        if (abs(a) > abs(b))
        {
            return a;
        }
        else if (abs(b) > abs(a))
        {
            return b;
        }
        return 0;
    }
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        // let's start pushing and poppping he he he
        stack<int> stk;
        for (int asteroid : asteroids)
        {
            if (stk.empty())
            {
                stk.push(asteroid);
            }
            else
            {
                if (areSameSigns(stk.top(), asteroid))
                {
                    stk.push(asteroid);
                }
                else
                {
                    if (stk.top() + asteroid == 0)
                    {
                        stk.pop();
                    }
                    else
                    {
                        int a = maxMagnitudeNumber(stk.top(), asteroid);
                        stk.pop();
                        stk.push(a);
                    }
                }
            }
        }
        vector<int> ans;
        while (!stk.empty())
        {
            ans.push_back(stk.top());
            stk.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

// Method 2:- Improved version
class Solution
{
public:
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        stack<int> stk;

        for (int asteroid : asteroids)
        {
            if (asteroid > 0)
            {
                stk.push(asteroid);
            }
            else
            {
                while (!stk.empty() && stk.top() > 0 && stk.top() < -asteroid)
                {
                    stk.pop();
                }

                if (stk.empty() || stk.top() < 0)
                {
                    stk.push(asteroid);
                }
                else if (stk.top() == -asteroid)
                {
                    stk.pop();
                }
            }
        }

        vector<int> result;
        while (!stk.empty())
        {
            result.push_back(stk.top());
            stk.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
int main()
{
}