#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *queue;  // Dynamic array to hold the elements
    int front;
    int rear;
    int size;
} ordQ;

void insertFront(int val, ordQ *Q) {
    if (Q->front == 0) {
        printf("Queue is full at the front. Do you want to resize? Y/N: ");
        char ch;
        scanf(" %c", &ch);
        if (ch == 'Y') {
            Q->size *= 2;
            int *newQueue = (int *)realloc(Q->queue, Q->size * sizeof(int));
            if (newQueue == NULL) {
                printf("Memory allocation failed. Exiting program.\n");
                exit(1); // Exit if realloc fails
            }
            Q->queue = newQueue;
        } else {
            return;
        }
    }
    if (Q->front == -1 && Q->rear == -1) {
        Q->front = Q->rear = 0;
    } else {
        Q->front--;  // Decrement the front to insert at the front
    }

    Q->queue[Q->front] = val; 
}

void deleteRear(ordQ *Q) {
    if (Q->rear == -1) {
        printf("Queue is empty\n");
        return;
    }
    printf("Deleted element from rear: %d\n", Q->queue[Q->rear]);
    if (Q->front == Q->rear) {
        Q->front = Q->rear = -1;  // Reset queue if it's empty
    } else {
        Q->rear--;  // Decrement the rear pointer
    }
}

void display(ordQ *Q) {
    if (Q->front == -1) {
        printf("Queue is empty\n");
        return;
    }

    for (int i = Q->front; i <= Q->rear; i++) {
        printf("%d ", Q->queue[i]);
    }
    printf("\n");
}

int main() {
    ordQ Q;
    Q.queue = (int *)malloc(100 * sizeof(int));
    Q.size = 100;
    Q.front = Q.rear = -1;

    int ch, val;
    do {
        printf("Enter 0 to insert at front\n1 to delete from rear\n2 to display\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 0:
                printf("Enter the value to be inserted at the front: ");
                scanf("%d", &val);
                insertFront(val, &Q);
                break;
            case 1:
                deleteRear(&Q);
                break;
            case 2:
                display(&Q);
                break;
            default:
                ch = 4; // Exit
        }
    } while (ch < 4);

    free(Q.queue);
    return 0;
}
