#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data ;
    struct Node * next ;
}Node;
Node * Start = NULL ;
void insertbeg ()
{
    Node * N1 = (Node * ) malloc (1*sizeof (Node ));
    printf ("Enter your data ");
    scanf ("%d", &N1->data);
    N1->next = Start;
    Start = N1;
}
void insertend ()
{
    Node * N1 = (Node * ) malloc (1*sizeof (Node));
    printf ("Enter your data ");
    scanf ("%d", &N1->data);
    Node * p = Start ;
    while (p->next != NULL)
          p = p->next ;
    p->next = N1 ;
    N1->next = NULL;
}
void insertpos ()
{
    int c = 0, pos;
    printf ("Enter position ");
    scanf ("%d", &pos);
    if (pos == 0)
    {
       insertbeg();
       return ;
    }
    Node * N1 = (Node *) malloc (1*sizeof (Node));
    printf ("Enter your data ");
    scanf ("%d" , &N1->data);
    Node * p = Start ;
    while (p->next != NULL && c < pos-1){
          p = p->next;
          c++;
    }
    N1->next = p->next;
    p->next = N1;
}
void deletebeg ()
{
    if (Start != NULL)
    Start = Start->next;
}
void deleteend ()
{
    if (Start != NULL){
       Node * p = Start ;
       while (p->next->next != NULL)
            p = p->next ;
       p->next = NULL ;
    }
}
void deletepos ()
{
    if (Start != NULL){
       int c = 0, pos;
       printf ("Enter position ");
       scanf ("%d", &pos);
       if (pos == 0)
       {
         deletebeg();
          return ;
       }
       Node * p = Start;
       while (p->next != NULL && c < pos-1)
       {
          p = p->next ;
          c++;
       }
       p->next = p->next->next;
    }
}
void search() 
{
    Node * p = Start;
    Node * curr = NULL;
    int ele, flag = 0;
    
    printf("Enter your element to be searched: ");
    scanf("%d", &ele);
    
    while (p != NULL) 
    {
        if (p->data == ele) 
        {
            printf("Element found: %d with memory address: %p\n", p->data, (void*)p);
            
            if (curr != NULL) 
            {
                printf("Previous node: %d with address: %p\n", curr->data, (void*)curr);
            } 
            else 
            {
                printf("No previous node (this is the first node)\n");
            }
            
            flag = 1;  // Element found
        }
        
        curr = p;
        p = p->next;
    }

    if (flag == 0) 
    {
        printf("Node with data %d not found\n", ele);
    }
}

void display ()
{
    Node * ptr = Start ;
    while (ptr != NULL)
    {
        printf ("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main ()
{
    int ch ;
    void (* funcpointer[8])() = {insertbeg , insertend , insertpos , deletebeg , deleteend, deletepos ,search ,display};
    do {
        printf (" Enter 0 to insert at beginning\n 1 to insert at end\n 2 to insert at position\n 3 to delete at beginning \n 4 to delete at end \n 5 to delete at position \n 6 to search \n 7 to display\n");
        printf ("Enter your choice ");
        scanf ("%d", &ch);
        if (ch > -1 && ch < 8)
           funcpointer [ch]() ;
        else ch = 9 ;
    }while (ch != 9);
    while (Start != NULL) {
        deletebeg();
    }
    return 0 ;
}