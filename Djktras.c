#include <stdio.h>
#include <limits.h>
#define V 4 

int minDistance(int dist[], int sptSet[]) 
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) 
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src) 
{
    int dist[V]; 
    int sptSet[V];
    for (int i = 0; i < V; i++) 
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) 
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < V; v++) 
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) 
    {
        printf("%d\t\t%d\n", i, dist[i]);
    }
}

int main() {
    // Graph represented by an adjacency matrix
    int graph[V][V] = {
        {0, 5, 1, 0},
        {5, 0, 0, 2},
        {1, 0, 0, 3},
        {0, 2, 3, 0}
    };

    // Run Dijkstra's Algorithm from source vertex 0
    dijkstra(graph, 0);

    return 0;
}
