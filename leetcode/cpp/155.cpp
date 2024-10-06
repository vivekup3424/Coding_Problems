#include <bits/stdc++.h>
using namespace std;

class MinStack
{
    // Naive Approach
public:
    stack<pair<int, int>> stk;
    MinStack()
    {
        ;
    }

    void push(int val)
    {
        if (stk.size() == 0)
        {
            stk.push({val, val});
        }
        else
        {
            int mini = min(val, stk.top().second);
            stk.push({val, mini});
        }
    }

    void pop()
    {
        if (stk.size() > 0)
        {
            stk.pop();
        }
    }

    int top()
    {
        return stk.top().first;
    }

    int getMin()
    {
        try
        {
            stk.top().second;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */