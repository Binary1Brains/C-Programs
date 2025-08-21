#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct Node {
 int data;
  struct Node * ptr;
}Node;

Node * XOR (Node *a, Node * b)
{
  return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void insert (Node ** Start, int data)
{
  Node * N  = (Node*) malloc (sizeof(Node));
  N->data = data;
  N->ptr  = *Start;
  if (*Start != NULL)
  {
    (*Start)->ptr = XOR(N, (*Start)->ptr);
  }
  *Start = N;
}

void print (Node * Start )
{
  Node * curr = Start;
  Node * prev = NULL;
  Node * next;
  printf("Linked List : ");
  while (curr != NULL)
  {
    printf ("%d ", curr->data);
    next = XOR(prev, curr->ptr);
    prev = curr;
    curr = next;
  }
  printf("\n");
}

void freell (Node * Start)
{
  Node * curr = Start;
  Node * prev = NULL;
  Node * next ;
  while (curr != NULL)
  {
    next = XOR (prev, curr->ptr);
    free (curr);
    prev = curr;
    curr = next;
  }
}

int main ()
{
  Node * Start = NULL;
  int n, ch;
  do{
    printf ("Enter your choice i - insert, d - display, q - quit ");
    scanf (" %c", &ch);
    switch (ch) {
      case 'i': 
      printf ("Enter your data ");
      scanf ("%d", &n);
      insert(&Start, n);
      break;
      case 'd':
      if (Start == NULL)
        {
          printf ("List Empty \n");
          break;
      }
      print (Start);
      break;
      case 'q':
      break;
      default:
      printf ("Wrong choice \n");
    }
  }while (ch != 'q');
  freell(Start);
}
