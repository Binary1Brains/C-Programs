#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *Start = NULL;

void insertend() {
    Node *N1 = (Node *)malloc(1 * sizeof(Node));
    printf("Enter your data: ");
    scanf("%d", &N1->data);
    N1->next = NULL;

    if (Start == NULL) {
        Start = N1;
    } else {
        Node *p = Start;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = N1;
    }
}

int issorted() {
    if (Start == NULL) 
        return 0;

    Node *p = Start;
    if (p->next == NULL)
       return -2;
    int flag = 0;
    while (p->next != NULL) {
        if (p->data < p->next->data) 
        {
            if (flag == 0) 
                flag = 1; 
            else if (flag == -1) 
                return 0;
        } 
        else if (p->data > p->next->data) 
        {
            if (flag == 0) 
                flag = -1;
            else if (flag == 1)
                return 0; 
        }
        p = p->next;
    }

    return flag;
}

int main() 
{
    int flag = 1;
    do {
        insertend();
        printf("Do you want to exit (0/1)? ");
        scanf("%d", &flag);
    } while (flag);

    int a = issorted();
    printf((a == 1)?"Ascending":(a == -1)? "Descending":(a == -2)?"Sorted":"Un-sorted" );
    return 0;
}
