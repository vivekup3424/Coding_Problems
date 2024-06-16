#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

const int MAX_N = 2e5;

int N;
int ans[MAX_N];
vector<pair<pair<int, int>, int>> v(MAX_N);

int main()
{
    cin >> N;
    v.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i].first.first >> v[i].first.second;
        v[i].second = i; // store the original index
    }
    sort(v.begin(), v.end());

    int rooms = 0, last_room = 0;
    priority_queue<pair<int, int>> pq; // min heap to store departure times.
    for (int i = 0; i < N; i++)
    {
        if (pq.empty())
        {
            last_room++;
            // make the departure time negative so that we create a min heap
            // (cleanest way to do a min heap... default is max in c++)
            pq.push(make_pair(-v[i].first.second, last_room));
            ans[v[i].second] = last_room;
        }
        else
        {
            // accessing the minimum departure time
            pair<int, int> minimum = pq.top();
            if (-minimum.first < v[i].first.first)
            {
                pq.pop();
                pq.push(make_pair(-v[i].first.second, minimum.second));
                ans[v[i].second] = minimum.second;
            }

            else
            {
                last_room++;
                pq.push(make_pair(-v[i].first.second, last_room));
                ans[v[i].second] = last_room;
            }
        }

        rooms = max(rooms, int(pq.size()));
    }

    cout << rooms << "\n";
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }
}