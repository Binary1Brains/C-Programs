#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct EdgeItem {
    int u, v, w;
} EdgeItem;

typedef struct Vertex {
    int d;
    int pi;
    int inheap;
} Vertex;

typedef struct Edge {
    int w;
    int in;
} Edge;

typedef struct Graph {
    int S;
    Vertex *V;
    Edge **E;
} Graph;

typedef struct Subset {
    int parent;
    int rank;
} Subset;

void sortEdges(EdgeItem *edges, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (edges[j].w > edges[j + 1].w)
            {
                EdgeItem temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}


int findSet(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = findSet(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSet(Subset subsets[], int x, int y)
{
    int xroot = findSet(subsets, x);
    int yroot = findSet(subsets, y);
    if (xroot == yroot)
        return;
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}


void Kruskal(Graph *G)
{
    int V = G->S;
    int maxEdges = V * V;
    EdgeItem *edgeList = malloc(maxEdges * sizeof(EdgeItem));
    int edgeCount = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (G->E[i][j].in)
            {
                edgeList[edgeCount].u = i;
                edgeList[edgeCount].v = j;
                edgeList[edgeCount].w = G->E[i][j].w;
                edgeCount++;
            }
        }
    }
    sortEdges(edgeList, edgeCount);
    Subset *subsets = malloc(V * sizeof(Subset));
    for (int i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    int totalWeight = 0;
    printf("Kruskal's MST:\n");
    for (int i = 0, e = 0; e < V - 1 && i < edgeCount; i++)
    {
        int u = edgeList[i].u;
        int v = edgeList[i].v;
        int set_u = findSet(subsets, u);
        int set_v = findSet(subsets, v);
        if (set_u != set_v)
        {
            printf("Edge %d - %d (weight %d)\n", u, v, edgeList[i].w);
            totalWeight += edgeList[i].w;
            unionSet(subsets, set_u, set_v);
            e++;
        }
    }
    printf("Total MST Weight: %d\n", totalWeight);
    free(edgeList);
    free(subsets);
}

Graph *createGraph (int S)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->S = S;
    G->V = (Vertex *)malloc(S * sizeof(Vertex));
    G->E = (Edge **)malloc(S * sizeof(Edge *));
    for (int i = 0; i < S; i++) 
    {
        G->E[i] = (Edge *)malloc(S * sizeof(Edge));
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
    G->E[u][v].w = w;
    G->E[u][v].in = 1;
    G->E[v][u].w = w;
    G->E[v][u].in = 1;
}


int main()
{
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    Graph *G = createGraph(V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges in format: u v w \n");
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(G, u, v, w);
    }
    Kruskal(G);
    for (int i = 0; i < V; i++)
    {
        free(G->E[i]);
    }
    free(G->E);
    free(G->V);
    free(G);
    return 0;
}