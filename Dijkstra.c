#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int mindis (int *dis, int *sptset, int V)
{
    int main = INT_MAX, minindex;
    for (int v = 0 ; v < V; v++)
    {
        if (sptset[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            minindex = v;
        }
    }
    return minindex;
}

int dijkstra (int ** graph, int src , int V)
{
    int *dist = (int*)malloc (V*sizeof(int));
    int *sptset = (int*)malloc (V*sizeof(int));
    for (int i = 0 ; i< V ; i++)
    {
        dist[i] = INT_MAX;
        sptset[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0 ; i < V; i++)
    {
        int u = mindis(dist, sptset,V);
        sptset[u] = 1;
        for (int j = 0; j < V; j++)
        {
            if(!sptset[v] && graph[u][v] && dist[u] != INT_MAX )
        }
    }
}