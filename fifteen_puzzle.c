#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE_SIZE 100003
#define MAX_KEY_LEN 256

typedef struct Node {
    int **matrix;
    int n;
    int x, y;
    int cost;
    int level;
    struct Node *parent;
} Node;

typedef struct PriorityQueue {
    Node **nodes;
    int size;
    int capacity;
} PriorityQueue;

typedef struct HashTable {
    char **keys;
    int *used;
    int size;
    int capacity;
} HashTable;

char * serializeMatrix (int ** matrix, int n);
int ** allocateMatrix (int n)
{
    int ** matrix = (int**) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *) malloc(n * sizeof(int));
    return matrix;
}

void freeMatrix(int ** matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

int ** copyMatrix(int ** matrix, int n)
{
    int ** newMatrix = allocateMatrix (n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            newMatrix[i][j] = matrix[i][j];
    return newMatrix;
}

int heuristic (int ** matrix, int n)
{
    int dist = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
	{
            int val = matrix[i][j];
            if (val != 0)
	    {
                int goalX = (val - 1) / n;
                int goalY = (val - 1) % n;
                dist += abs(i - goalX) + abs(j - goalY);
            }
        }
    return dist;
}


void initPQ (PriorityQueue *pq, int capacity)
{
    pq->size = 0;
    pq->capacity = capacity;
    pq->nodes = (Node **) malloc(capacity * sizeof(Node *));
}

void resizePQ (PriorityQueue * pq)
{
    pq->capacity *= 2;
    pq->nodes = realloc(pq->nodes, pq->capacity * sizeof(Node *));
}

void push (PriorityQueue * pq, Node * node)
{
    if (pq->size == pq->capacity)
        resizePQ(pq);
    int i = pq->size++;
    pq->nodes[i] = node;
    while (i > 0 && pq->nodes[i]->cost < pq->nodes[(i - 1) / 2]->cost)
    {
        Node *tmp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
}

Node * pop (PriorityQueue * pq)
{
    if (pq->size == 0) return NULL;
    Node *top = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (2 * i + 1 < pq->size)
    {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (pq->nodes[left]->cost < pq->nodes[smallest]->cost)
            smallest = left;
        if (right < pq->size && pq->nodes[right]->cost < pq->nodes[smallest]->cost)
            smallest = right;
        if (smallest == i) break;
        Node *tmp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[smallest];
        pq->nodes[smallest] = tmp;
        i = smallest;
    }
    return top;
}

unsigned long hash (char * key)
{
    unsigned long h = 5381;
    for (int i = 0; key[i]; i++)
        h = ((h << 5) + h) + key[i];
    return h % TABLE_SIZE;
}

void initHashTable (HashTable * ht)
{
    ht->keys = calloc(TABLE_SIZE, sizeof(char *));
    ht->used = calloc(TABLE_SIZE, sizeof(int));
    ht->capacity = TABLE_SIZE;
    ht->size = 0;
}

int isVisited (HashTable * ht, char * key)
{
    unsigned long idx = hash(key);
    while (ht->keys[idx])
    {
        if (strcmp(ht->keys[idx], key) == 0)
            return 1;
        idx = (idx + 1) % ht->capacity;
    }
    return 0;
}

void insertHash (HashTable * ht, char * key)
{
    unsigned long idx = hash(key);
    while (ht->keys[idx])
        idx = (idx + 1) % ht->capacity;
    ht->keys[idx] = key;
    ht->used[idx] = 1;
}

void freeHashTable (HashTable * ht)
{
    for (int i = 0; i < ht->capacity; i++)
        if (ht->keys[i]) free(ht->keys[i]);
    free(ht->keys);
    free(ht->used);
}

int isGoal (int ** matrix, int n)
{
    int val = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
	{
            if (i == n - 1 && j == n - 1)
                return matrix[i][j] == 0;
            if (matrix[i][j] != val++) return 0;
        }
    return 1;
}

void printMatrix (int ** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf ("%2d ", matrix[i][j]);
        printf ("\n");
    }
    printf("\n");
}

void printPath (Node *node)
{
    if (node == NULL) return;
    printPath(node->parent);
    printMatrix(node->matrix, node->n);
}

int isSafe (int x, int y, int n)
{
    return x >= 0 && y >= 0 && x < n && y < n;
}

Node * newNode (int ** matrix, int n, int x, int y , int newX, int newY, int level, Node * parent)
{
    Node * node = (Node *) malloc(sizeof(Node));
    node->matrix = copyMatrix(matrix, n);
    node->n = n;
    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;
    int temp = node->matrix[x][y];
    node->matrix[x][y] = node->matrix[newX][newY];
    node->matrix[newX][newY] = temp;
    node->cost = heuristic(node->matrix, n) + level;
    return node;
}

int solve (int ** initial , int n, int x , int y) 
{
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    PriorityQueue pq;
    initPQ(&pq, 128);
    HashTable ht;
    initHashTable(&ht);
    Node *start = newNode(initial, n, x, y, x, y, 0, NULL);
    push(&pq, start);
    insertHash(&ht, serializeMatrix(initial, n));
    while (pq.size > 0)
    {
        Node * node = pop(&pq);
        if (isGoal(node->matrix, n))
	{
            printf ("Solution found!\n");
            printPath(node);
            freeHashTable(&ht);
            free(pq.nodes);
            return 1;
        }
        for (int i = 0; i < 4; i++) {
            int newX = node->x + dx[i];
            int newY = node->y + dy[i];
            if (isSafe(newX, newY, n)) {
                Node * child = newNode(node->matrix, n, node->x, node->y, newX, newY, node->level + 1, node);
                char * key = serializeMatrix(child->matrix, n);
                if (!isVisited(&ht, key))
		{
                    insertHash (&ht, key);
                    push(&pq, child);
                }
		else
		{
                    free(key);
                    freeMatrix(child->matrix, n);
                    free(child);
                }
            }
        }
    }
    freeHashTable(&ht);
    free(pq.nodes);
    return 0;
}

int isSolvable (int ** matrix, int n) {
    int *arr = (int*)malloc(n * n * sizeof(int));
    int k = 0, inversions = 0, blankRow = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0)
                blankRow = i;
            arr[k++] = matrix[i][j];
        }

    for (int i = 0; i < n * n - 1; i++)
        for (int j = i + 1; j < n * n; j++)
            if (arr[i] && arr[j] && arr[i] > arr[j])
                inversions++;
    free(arr);
    if (n % 2 == 1) 
	    return inversions % 2 == 0;
    return (inversions + blankRow) % 2 == 1;
}

char * serializeMatrix(int ** matrix, int n)
{
    int maxLen = n * n * 6;
    char *str = (char *) malloc(maxLen);
    str[0] = '\0';
    char temp[6];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            sprintf(temp, "%d,", matrix[i][j]);
            strcat(str, temp);
        }
    return str;
}

int main()
{
    int n;
    printf ("Enter puzzle size: ");
    scanf("%d", &n);
    if (n < 2)
    {
        printf("Puzzle size must be at least 2.\n");
        return 1;
    }
    int **initial = allocateMatrix(n);
    int x = 0, y = 0;
    printf ("Enter the puzzle (%dx%d), use 0 for blank:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    if (!isSolvable(initial, n))
    {
        printf("This puzzle is unsolvable.\n");
        freeMatrix(initial, n);
        return 1;
    }
    if (!solve(initial, n, x, y))
        printf ("No solution found.\n");
    freeMatrix(initial, n);
    return 0;
}
