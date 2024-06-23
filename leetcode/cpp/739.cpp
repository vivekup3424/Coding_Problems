#include <bits/stdc++.h>
using namespace std;
// Method 1:- Using two pointer approach, I am getting TLE here
class Solution1
{
public:
    vector<int> dailyTemperatures(vector<int> &temp)
    {
        int i = 0;
        vector<int> result;
        while (i < temp.size())
        {
            int j = i;
            while (temp[j] <= temp[i] and j < temp.size())
            {
                j++;
            }
            result.push_back(j - i);
        }
        return result;
    }
};
class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temp)
    {
        stack<pair<int, int>> s; // stores the number as well as the index
    }
};
struct ListNode
{
    int data;
    struct ListNode *next;
};
class A
{
public:
    vector<int> v;
    void func()
    {
        vector<int> v2 = new vector(4, 9);
        A B = new Class A;
    }
};
int main()
{
}