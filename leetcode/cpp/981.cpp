#include <bits/stdc++.h>
#include <string>
using namespace std;

class TimeMap
{
public:
    map<string,vector<pair<int,string>>> events;
    TimeMap()
    {
        ;
    }

    void set(string key, string value, int timestamp)
    {
        events[key].push_back({timestamp,value});
    }

    string get(string key, int timestamp)
    {
        //if key doesn't exists
        if(events.find(key)==events.end()){
            return "";
        }
        int l = 0, r = events[key].size()-1, m = 0;
        int ans = -1;
        while(l<=r){
            m = (l+r)/2;
            if(events[key][m].first <= timestamp){
                ans = m;
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        return (ans == -1) ? "" : events[key][ans].second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
