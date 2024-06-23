#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

struct Guy
{
    int id;
    int level;
};

struct Movie
{
    int frequency;
    string name;
};

class Solution
{
public:
    vector<string> watchedVideosByFriends(vector<vector<string>> &watchedVideos, vector<vector<int>> &friends, int id, int level)
    {
        // Create the graph
        int n = friends.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++)
        {
            for (auto guysId : friends[i])
            {
                adj[i].push_back(guysId);
            }
        }

        // Debug: Print the graph
        for (int i = 0; i < n; i++)
        {
            cout << "Dude = " << i << endl;
            cout << "Friends = :-\n";
            outputVector(adj[i], adj[i].size());
        }

        // Get the id of the friends at the given level using BFS
        queue<Guy> q;
        q.push({id, 0});
        vector<bool> visited(n, false);
        visited[id] = true;
        vector<int> guysAtRequiredLevel;

        while (!q.empty())
        {
            Guy someGuy = q.front();
            q.pop();
            if (someGuy.level == level)
            {
                guysAtRequiredLevel.push_back(someGuy.id);
            }
            else if (someGuy.level < level)
            {
                // Visit all the friends of this dude
                for (auto friendId : adj[someGuy.id])
                {
                    if (!visited[friendId])
                    {
                        q.push({friendId, someGuy.level + 1});
                        visited[friendId] = true;
                    }
                }
            }
        }

        unordered_map<string, int> freqHashMap;
        for (auto id : guysAtRequiredLevel)
        {
            for (auto &movie : watchedVideos[id])
            {
                freqHashMap[movie]++;
            }
        }

        vector<Movie> movies;
        for (auto &it : freqHashMap)
        {
            movies.push_back({it.second, it.first});
        }

        // Sort movies by frequency and then by name
        sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b)
             {
            if (a.frequency == b.frequency)
                return a.name < b.name;
            return a.frequency < b.frequency; });

        vector<string> result;
        for (auto &movie : movies)
        {
            result.push_back(movie.name);
        }

        return result;
    }
};

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        int n, m, id, level;
        cin >> n >> m >> id >> level;

        vector<vector<string>> watchedVideos(n);
        vector<vector<int>> friends(n);

        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            watchedVideos[i].resize(k);
            for (int j = 0; j < k; j++)
            {
                cin >> watchedVideos[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            friends[i].resize(k);
            for (int j = 0; j < k; j++)
            {
                cin >> friends[i][j];
            }
        }

        Solution sol;
        vector<string> result = sol.watchedVideosByFriends(watchedVideos, friends, id, level);

        for (auto &str : result)
        {
            cout << str << " ";
        }
        cout << "\n";
    }
    return 0;
}
