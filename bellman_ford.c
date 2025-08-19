#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Vertex {
    int pi;
    int d;
} Vertex;

typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct Graph {
    int V, E;
    Vertex *v;
    Edge *e;
} Graph;

void Initialize_single_source(Graph *G, int src)
{
    for (int i = 0; i < G->V; i++)
    {
        G->v[i].d = INT_MAX;
        G->v[i].pi = -1;
    }
    G->v[src].d = 0;
}

void Relax(Vertex *u, Vertex *v, Edge e)
{
    if (u->d != INT_MAX && v->d > u->d + e.weight) 
    {
        v->d = u->d + e.weight;
        v->pi = e.src;
    }
}

bool Bellman_Ford(Graph *G, int src)
{
    Initialize_single_source(G, src);
    for (int i = 1; i < G->V; i++)
    {
        for (int j = 0; j < G->E; j++)
	{
            Edge e = G->e[j];
            Relax(&G->v[e.src], &G->v[e.dest], e);
        }
    }
    for (int j = 0; j < G->E; j++)
    {
        Edge e = G->e[j];
        if (G->v[e.dest].d > G->v[e.src].d + e.weight) 
            return false;
    }
    return true;
}

int main ()
{
	int V, E;
	printf ("Enter number of vertex ");
	scanf("%d", &V);
	printf("Enter number of edges ");
	scanf("%d", &E);
	Graph * G = (Graph *) malloc (sizeof(Graph));
	G->V = V;
	G->E = E;
	G->v = (Vertex *) malloc (V * sizeof (Vertex));
	G->e = (Edge* ) malloc (E* sizeof (Edge));
	printf ("Enter vertex connected vertex weight \n");
	for (int i = 0; i < E; i++)
	{
		scanf ("%d %d %d", &G->e[i].src, &G->e[i].dest, &G->e[i].weight);
	}
	int src, dest;
	printf("Enter the source vertex ");
	scanf("%d", &src);
	if (Bellman_Ford(G, src))
		for(int i = 0; i < V; i++)
			printf("Vertex %d: Distance %d, Predecessor %d\n ", i, G->v[i].d, G->v[i].pi);
	else
		printf ("Negative weight cycle \n");
	printf ("Enter Destination ");
	scanf ("%d", &dest);
	if (G->v[dest].d == INT_MAX)
	{
		printf("No path from source to vertex %d\n", dest);
		return 0 ;
	}
	printf("Path to vertex %d: ", dest);
	int current = dest, size = 0;
	int * path = (int *) malloc (V * sizeof (int));
	while (current != -1)
	{
		path[size++] = current;
		current = G->v[current].pi;
	}
	for (int i = size-1; i >= 0; i--)
		printf("%d ", path[i]);
	printf("\n");
	free (G->v);
	free (G->e);
	free(G);
	free (path);
	return 0;
}
