
#include <bits/stdc++.h>
using namespace std;
class MyHashSet
{
public:
    bool visited[1000001];
    MyHashSet()
    {
        fill(visited, visited + 1000000, false);
    }

    void add(int key)
    {
        visited[key] = true;
    }

    void remove(int key)
    {
        visited[key] = false;
    }

    bool contains(int key)
    {
        return visited[key];
    }
};

int main()
{
}