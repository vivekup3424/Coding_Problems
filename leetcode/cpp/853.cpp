
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int carFleet(int target, vector<int> &position, vector<int> &speed)
    {
        stack<int> s; // this will store the index of elements
        // if new_element <= s.top(), then s.push()
        // else s.pop() and increment the counter
        int count = 1;
        int time = (target - position[0]) / speed[0]; // initial time-taken
        for (int i = 0; i < position.size(); i++)
        {
            while (!s.empty() and position[s.top()] + time * speed[s.top()] < (position[i] + time * speed[i]))
            {
                count++;
                while (!s.empty())
                {
                    s.pop();
                }
                time = (target - position[i]) / speed[i];
            }
            s.push(i);
        }
        return count;
    }
};
int main()
{
}
