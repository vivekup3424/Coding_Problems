#include <iostream>
#include <limits.h>
using namespace std;

#define V 9

// returns the minimum distance vertex
int minDistance(int dist[], bool sptSet[])
{
    int minValue = INT_MAX, min_index;
    for (int i = 1; i <= sizeof(dist) / sizeof(int); i++) // vertices start from 1
    {
        if (dist[i] < minValue)
        {
            minValue = dist[i];
            min_index = i;
        }
    }
    return i;
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V + 1];
    bool sptSet[V + 1];

    // initialize all distance as infinite
    for (int i = 1; i <= V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;
}