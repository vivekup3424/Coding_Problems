#include <bits/stdc++.h>
using namespace std;

using namespace std;

class CustomStack
{
private:
    vector<int> arr;
    int capacity = 0;
    int index = -1;

public:
    CustomStack(int maxSize)
    {
        this->capacity = maxSize;
        this->index = -1;
        arr.resize(capacity);
    }
    void push(int x)
    {
        index++;
        if (index >= capacity)
        {
            index = capacity - 1; // pointing to the last occupied index
        }
        else
        {
            arr[index] = x;
        }
        return;
    }
    int pop()
    {
        if (index >= 0)
        {
            return arr[index--];
        }
        else
        {
            index = -1;
        }
        return -1;
    }
    void increment(int k, int val)
    {
        // start from the last index and go till index-k+1
        for (int i = index; i >= index - k + 1; i--)
        {
            if (i < 0)
            {
                break;
            }
            else
            {
                arr[i] += val;
            }
        }
        return;
    }
};