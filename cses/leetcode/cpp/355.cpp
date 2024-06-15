#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// use a hashmap to store a list of id's that a useid follows
class Twitter
{
private:
    int time;

public:
    map<int, set<int>> hashmap;
    map<int, priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>>> messages;
    Twitter()
    {
        time = 0;
    }

    void postTweet(int userId, int tweetId)
    {
        time++;
        messages[userId].push({time, tweetId});
    }

    vector<int> getNewsFeed(int userId)
    {
        // Retrieves the 10 most recent tweet IDs in the
    }

    void follow(int followerId, int followeeId)
    {
        hashmap[followeeId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        hashmap[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */