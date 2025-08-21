#include <stdio.h>
#include <stdlib.h>
#define isEmpty(q) (q->front == NULL)
#define isFull(q) (q->size == q->maxSize)

struct Node 
{
    int data;
    struct Node* next;
};

struct Queue 
{
    struct Node* front;
    struct Node* rear;
    int size;     
    int maxSize;  
};

struct Node* createNode(int data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initQueue(struct Queue* q, int maxSize) 
{
    q->front = q->rear = NULL;
    q->size = 0;
    q->maxSize = maxSize; 
}

void enqueue(struct Queue* q, int data) 
{
    if (isFull(q)) 
    {
        printf("Queue is full! Cannot enqueue %d\n", data);
        return;
    }
    
    struct Node* newNode = createNode(data);
    if (isEmpty(q)) 
    {
        q->front = q->rear = newNode;
    } else 
    {
        q->rear->next = newNode;  
        q->rear = newNode;       
    }
    q->size++;  
    printf("%d enqueued to queue\n", data);
}

int dequeue(struct Queue* q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty\n");
        return -1;
    }
    struct Node* temp = q->front;
    int dequeuedData = temp->data;
    q->front = q->front->next; 
    if (q->front == NULL) 
    {
        q->rear = NULL;  
    }
    free(temp); 
    q->size--;  
    return dequeuedData;
}

int peek(struct Queue* q) 
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty\n");
        return -1; 
    }
    return q->front->data;
}

void displayQueue(struct Queue* q)
{
    if (isEmpty(q)) 
    {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) 
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() 
{
    struct Queue q;
    initQueue(&q, 3);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    displayQueue(&q);
    enqueue(&q, 40);
    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);
    printf("Peek front: %d\n", peek(&q));
    return 0;
}
