#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int time = 0;

typedef struct Vertex {
    int color;
    int d;   
    int f;  
    int pi; 
} Vertex;

typedef struct Edge {
    int in;
    int w;
} Edge;

typedef struct Graph {
    int S;
    Vertex *V;
    Edge **E;
} Graph;


Graph *createGraph(int S)
{
    Graph *G = malloc(sizeof(Graph));
    G->S = S;
    G->V = malloc(S * sizeof(Vertex));
    G->E = malloc(S * sizeof(Edge *));
    for (int i = 0; i < S; i++)
    {
        G->E[i] = malloc(S * sizeof(Edge));
        for (int j = 0; j < S; j++)
        {
            G->E[i][j].in = 0;
            G->E[i][j].w = INT_MAX;
        }
    }
    return G;
}

void addEdge(Graph *G, int u, int v, int w)
{
    G->E[u][v].in = 1;
    G->E[u][v].w = w;
    G->E[v][u].in = 1;
    G->E[v][u].w = w;
}

void DFS_Visit(Graph *G, int u)
{
    time++;
    G->V[u].d = time;
    G->V[u].color = GRAY;
    printf("%d ", u);
    for (int v = 0; v < G->S; v++)
    {
        if (G->E[u][v].in && G->V[v].color == WHITE)
        {
            G->V[v].pi = u;
            DFS_Visit(G, v);
        }
    }
    G->V[u].color = BLACK;
    time++;
    G->V[u].f = time;
}

void DFS(Graph *G)
{
    for (int i = 0; i < G->S; i++)
    {
        G->V[i].color = WHITE;
        G->V[i].pi = -1;
    }
    time = 0;
    printf("DFS Traversal:\n");
    for (int i = 0; i < G->S; i++)
    {
        if (G->V[i].color == WHITE)
            DFS_Visit(G, i);
    }
    printf("\n");
}

int main()
{
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    Graph *G = createGraph(V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges in format u v w:\n");
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(G, u, v, w);
    }
    DFS(G);
    for (int i = 0; i < V; i++)
        free(G->E[i]);
    free(G->E);
    free(G->V);
    free(G);
    return 0;
}