#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct Vertex {
    int color;
    int d;  
    int pi; 
} Vertex;

typedef struct Edge {
    int in;
    int w;
} Edge;

typedef struct Graph{
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

void BFS(Graph *G, int start)
{
    int V = G->S;
    int *queue = malloc(V * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i < V; i++)
    {
        G->V[i].color = WHITE;
        G->V[i].d = INT_MAX;
        G->V[i].pi = -1;
    }
    G->V[start].color = GRAY;
    G->V[start].d = 0;
    G->V[start].pi = -1;
    queue[rear++] = start;
    printf("BFS Traversal:\n");
    while (front < rear)
    {
        int u = queue[front++];
        printf("%d ", u);
        for (int v = 0; v < V; v++)
        {
            if (G->E[u][v].in && G->V[v].color == WHITE)
            {
                G->V[v].color = GRAY;
                G->V[v].d = G->V[u].d + 1;
                G->V[v].pi = u;
                queue[rear++] = v;
            }
        }
        G->V[u].color = BLACK;
    }

    printf("\n");
    free(queue);
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
    int start;
    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);
    BFS(G, start);
    for (int i = 0; i < V; i++)
        free(G->E[i]);
    free(G->E);
    free(G->V);
    free(G);
    return 0;
}
