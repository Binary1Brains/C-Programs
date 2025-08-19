#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

typedef struct Edge {
    int u;
    int v;
    int weight;
} Edge;

typedef struct {
    int V;
    int E;
    Edge* edges;
} Graph;

Graph* create_graph(int V, int E)
{
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->edges = (Edge*)malloc(E * sizeof(Edge));
    return g;
}

int** build_adjacency_matrix(Graph* g)
{
    int n = g->V;
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) 
            dist[i][j] = (i == j) ? 0 : INT_MAX;
    }
    for (int i = 0; i < g->E; i++)
    {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int w = g->edges[i].weight;
        dist[u][v] = w; 
    }
    return dist;
}

int** build_predecessor_matrix(int** dist, int n)
{
    int** pred = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        pred[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            if (i == j || dist[i][j] == INT_MAX)
                pred[i][j] = -1;
            else
                pred[i][j] = i;
    }
    return pred;
}

void floyd_warshall(int** dist, int** pred, int n)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
}

void print_matrix(int** mat, int n, int show_inf)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (show_inf && mat[i][j] == INT_MAX)
                printf(" INF ");
            else
                printf("%4d ", mat[i][j]);
        printf("\n");
    }
}

void print_path(int** pred, int u, int v)
{
    if (u == v)
        printf("%d ", u);
    else if (pred[u][v] == -1)
        printf("No path from %d to %d", u, v);
    else
    {
        print_path(pred, u, pred[u][v]);
        printf("%d ", v);
    }
}

int tsp_dp(int** dist, int V)
{
    int dp[1 << V][V];
    for (int mask = 0; mask < (1 << V); mask++)
        for (int i = 0; i < V; i++)
            dp[mask][i] = INT_MAX;
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << V); mask++)
        for (int u = 0; u < V; u++)
            if (mask & (1 << u))
                for (int v = 0; v < V; v++)
                    if (mask & (1 << v))
                        if (v != u && dist[v][u] != INT_MAX)
                            dp[mask][u] = (dp[mask ^ (1 << u)][v] + dist[v][u] < dp[mask][u]) ? dp[mask ^ (1 << u)][v] + dist[v][u] : dp[mask][u];
    int min_cost = INT_MAX;
    for (int i = 1; i < V; i++)
        if (dist[i][0] != INT_MAX)
            min_cost = (dp[(1 << V) - 1][i] + dist[i][0] < min_cost) ? dp[(1 << V) - 1][i] + dist[i][0] : min_cost;
    return min_cost;
}

int main()
{
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    Graph* g = create_graph(V, E);
    printf("Enter each edge as: u v weight\n");
    for (int i = 0; i < E; i++) 
        scanf("%d %d %d", &g->edges[i].u, &g->edges[i].v, &g->edges[i].weight);
    int** dist = build_adjacency_matrix(g);
    int** pred = build_predecessor_matrix(dist, V);
    floyd_warshall(dist, pred, V);
    for (int i = 0; i < V; i++)
        if (dist[i][i] < 0)
        {
            printf("Graph contains a negative-weight cycle.\n");
            goto cleanup;
        }
    printf("\nAll-pairs shortest path matrix:\n");
    print_matrix(dist, V, 1);
    printf("\nPredecessor matrix:\n");
    print_matrix(pred, V, 0);
    int u, v;
    printf("\nEnter source and destination to print shortest path (e.g., 0 3): ");
    scanf("%d %d", &u, &v);
    printf("Shortest path from %d to %d: ", u, v);
    print_path(pred, u, v);
    printf("\n");
    int tsp_result = tsp_dp(dist, V);
    if (tsp_result == INT_MAX)
        printf("\nTSP: No Hamiltonian circuit exists.\n");
    else
        printf("\nMinimum cost Hamiltonian circuit (TSP): %d\n", tsp_result);

cleanup:
    for (int i = 0; i < V; i++)
    {
        free(dist[i]);
        free(pred[i]);
    }
    free(dist);
    free(pred);
    free(g->edges);
    free(g);
    return 0;
}
