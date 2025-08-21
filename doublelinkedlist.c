#include <stdlib.h>
#include <stdio.h>

typedef struct Node 
{
    int data ;
    struct Node * pre ;
    struct Node * next ;
}Node ;
Node * Start = NULL ;

void insertbeg ()
{
    Node *N1 = (Node * )malloc(1*sizeof (Node));
    if (N1 == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    printf ("Enter your data ") ;
    scanf ("%d" , &N1->data);
    N1->next = Start;
    N1->pre = NULL;
    if (Start != NULL)
          Start->pre = N1;
    Start = N1 ;
}
void insertend ()
{
    Node *N1 = (Node * )malloc(1*sizeof (Node));
    if (N1 == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    printf ("Enter your data ") ;
    scanf ("%d" , &N1->data);
    if (Start == NULL)
    {
        N1->next = NULL;
        N1->pre = NULL;
        Start = N1;
        return;
    }
    Node * p = Start ;
    N1->next = NULL;
    while (p->next != NULL)
        p = p->next ;
    p->next = N1;
    N1->pre = p ;
}
void insertpos ()
{
    Node * p = Start ;
    int pos ,c = 0 ;
    printf ("Enter your position ");
    scanf ("%d" , &pos);
    if (pos < 0)
    {
        printf ("Invalid position\n");
        return;
    }
    if (pos == 0)
    {
       insertbeg();
       return;
    }
    Node *N1 = (Node * )malloc(1*sizeof (Node));
    if (N1 == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    printf ("Enter your data ") ;
    scanf ("%d" , &N1->data);
    while (p != NULL && c < pos)
    {
        p = p->next ;
        c++;
    }
    if (p == NULL)
    {
        printf("Invalid position\n");
        free(N1);
        return;
    }
    N1->pre = p->pre;
    N1->next = p;
    if (p->pre != NULL)
        p->pre->next = N1;
    p->pre = N1;
}
void deletebeg ()
{
    if (Start != NULL)
    {
        Node *temp = Start;
        Start = Start->next;
        if (Start != NULL)
            Start->pre = NULL;
        free(temp);
    }
    else
       printf("List is empty\n");
}
void deleteend()
{
    if (Start != NULL)
    {
         Node * p = Start ;
         while (p->next != NULL)
             p = p->next ;
        if (p->pre != NULL)
             p->pre->next = NULL ;
        if (p == Start)
            Start = NULL;
        free (p) ;
    }
    else 
       printf("List is empty\n");
}
void deletepos ()
{
    if (Start != NULL)
    {
        Node * p = Start ;
        int pos ,c = 0 ;
        printf ("Enter your position ");
        scanf ("%d" , &pos);
        if (pos == 0)
        {
             deletebeg();
             return;
        }
        while (p != NULL && c < pos)
        {
             p = p->next ;
             c++;
        }
        if (p == NULL)
        {
            printf("Invalid position\n");
            return;
        }
       if (p->pre != NULL) 
            p->pre->next = p->next;
       if (p->next != NULL) 
           p->next->pre = p->pre;
    free (p);
    }
    else
       printf("List is empty\n");
}

void display ()
{
    Node * ptr = Start ;
    if (ptr == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (ptr != NULL)
    {
        printf ("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void search() 
{
    printf("Enter node to be searched: ");
    int search;
    scanf("%d", &search);

    Node *curr = NULL;
    Node *ptr = Start;

    if (ptr == NULL) 
    {
        printf("List is empty\n");
        return;
    }

    int found = 0;
    while (ptr != NULL) 
    {
        if (search == ptr->data) 
        {
            printf("Node found: %d with address %p\n", ptr->data, (void*)ptr);
            curr = ptr->pre;
            if (curr != NULL) 
            {
                printf("Previous node: %d with address %p\n", curr->data, (void*)curr);
            } 
            else
                printf("No previous node\n");
            found = 1;
        }
        ptr = ptr->next;
    }
    if (!found)
        printf("Node with data %d not found\n", search);
}


int main ()
{
    int ch ;
    void (* funcpointer[8])() = {insertbeg , insertend , insertpos , deletebeg , deleteend, deletepos ,display, search};
    do {
        printf (" Enter 0 to insert at beginning\n 1 to insert at end\n 2 to insert at position\n 3 to delete at beginning \n 4 to delete at end \n 5 to delete at position \n 6 to display\n 7 to search\n");
        printf ("Enter your choice ");
        scanf ("%d", &ch);
        if (ch > -1 && ch < 8)
           funcpointer [ch]() ;
        else 
            ch = 9 ;
    }while (ch != 9);
    while (Start != NULL) 
    {
        deletebeg();
    }
    return 0 ;
}