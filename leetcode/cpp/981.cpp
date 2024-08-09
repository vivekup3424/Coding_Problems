#include <bits/stdc++.h>
using namespace std;

class TimeMap
{
public:
    map<string, priority_queue<pair<int, string>>> mp;
    TimeMap()
    {
        ;
    }

    void set(string key, string value, int timestamp)
    {
        mp[key].push({timestamp, value});
    }

    string get(string key, int timestamp)
    {
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */