#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isNStraightHand(vector<int> &hand, int groupSize)
{
    int n = hand.size();
    if (n % groupSize != 0)
    {
        return false;
    }
    map<int, int> freqHashMap;
    for (auto h : hand)
    {
        freqHashMap[h]++;
    }
    // let's use map for searching, that way my
    // time complexity would be reduced to O(logn) for searching
    bool flag = true;
    for (auto it : freqHashMap)
    {
        while (freqHashMap[it.first] > 0)
        {
            for (int i = 0; i < groupSize; i++)
            {
                int element = it.first + i;
                if (freqHashMap.find(element) != freqHashMap.end())
                {
                    if (freqHashMap[element] == 0)
                    {
                        flag = false;
                        return flag;
                    }
                    else
                    {
                        freqHashMap[element]--;
                    }
                }
                else
                {
                    flag = false;
                    return flag;
                }
            }
        }
    }
    return true;
}
int main()
{
    vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    int groupSize = 3;
    cout << isNStraightHand(hand, groupSize) << endl;
}
