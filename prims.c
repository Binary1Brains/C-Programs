// min heapify for prims algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define Parent(i) (((i) - 1) / 2)
#define Left(i) (2 * (i) + 1)
#define Right(i) (2 * (i) + 2)
#define Swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct PQ {
	int heap_size;
	int * q;
	int * pos;
}PQ;

typedef struct Vertex {
	int d;
	int pi;
	int inheap;
}Vertex;

typedef struct Edge {
	int w;
	int in;
}Edge;

typedef struct Graph {
	int S;
	Vertex * V;
	Edge ** E;
}Graph;

int Minimum (PQ * Q)
{
	return Q->q[0];
}

void Min_heapify (PQ * Q, int i, Graph *G)
{
	int l = Left(i);
	int r = Right(i);
	int smallest = i;
	int temp;
	if (l < Q->heap_size && Q->q[l] < Q->q[i])
		smallest = l;
	if (r <= Q->heap_size && Q->q[r] < Q->q[smallest])
		smallest = r;
	if (smallest != i)
	{
		Q->pos[Q->q[i]] = smallest;
		Q->pos[Q->q[smallest]] = i;
		Swap (Q->q[i], Q->q[smallest], temp);
		Min_heapify (Q, smallest, G);
	}
}


int Extract_min (PQ * Q, Graph *G)
{
	if (Q->heap_size <= 0)
	{
		return -1;
	}
	int min = Q->q[0];
	Q->q[0] = Q->q[Q->heap_size - 1];
	Q->pos[Q->q[0]] = 0;
	Q->heap_size--;
	Min_heapify (Q, 0, G);
	return min;
}


void Decrease_key ( PQ * Q, Graph * G, int v, int nkey)
{
	int temp;
	int i = Q->pos[v];
	G->V[v].d = nkey;
	while (i && G->V[Q->q[i]].d < G->V[Q->q[Parent(i)]].d)
	{
		Q->pos[Q->q[i]] = Parent(i);
		Q->pos[Q->q[Parent(i)]] = i;
		Swap(Q->q[i], Q->q[Parent(i)], temp); 
		i = Parent(i);
	}
}


int is_in_heap (PQ * Q, int v)
{
	return Q->pos[v] < Q->heap_size;
}


void Prim (Graph * G, int r)
{
	int S = G->S;
	PQ Q;
	Q.q = malloc (S* sizeof(int));
	Q.pos = malloc (S * sizeof(int));
	Q.heap_size = S;
	for (int v = 0; v < S; v++)
	{
		G->V[v].d = INT_MAX;
		G->V[v].pi = -1;
		G->V[v].inheap = 1;
		Q.q[v] = v;
		Q.pos[v] = v;
	}
	G->V[r].d = 0;
	Decrease_key(&Q, G, r, 0);
	while (Q.heap_size > 0)
	{
		int u = Extract_min(&Q, G);
		G->V[u].inheap = 0;
		for (int v = 0; v < S; v++)
		{
			if (G->E[u][v].in && is_in_heap(&Q, v) && G->E[u][v].w < G->V[v].d)
			{
				G->V[v].pi = u;
				Decrease_key(&Q, G, v, G->E[u][v].w);
			}
		}
	}
	printf("Prims MST: \n");
	for (int i = 0; i < S; i++)
	{
		printf("Vertex %d Parent %d Key %d\n",i,G->V[i].pi, G->V[i].d);
	}
	free (Q.q);
	free (Q.pos);
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
    int start;
    printf("Enter the starting vertex for Prim's algorithm: ");
    scanf("%d", &start);
    Prim(G, start);
    for (int i = 0; i < V; i++)
    {
        free(G->E[i]);
    }
    free(G->E);
    free(G->V);
    free(G);
    return 0;
}