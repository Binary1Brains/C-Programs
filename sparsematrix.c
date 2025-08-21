#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int** arr;
    int** tuple;
    int row, col, i, j, col1 = 0 ;
    printf("Enter row of matrix ");
    scanf("%d", &row);
    tuple = malloc ((row*col) * sizeof (int*));
    arr = malloc (row * sizeof (int*));
    printf("Enter column of matrix ");
    scanf("%d", &col);
    for (i = 0 ; i < row ; i++)
    {
        arr[i] = malloc (col * sizeof (int));
        for (j = 0 ; j < col ; j++)
            scanf ("%d", &arr[i][j]);
    }
    for (i=0 ; i < (row*col); i++)
            tuple [i] = malloc (3*sizeof (int));
    for (i = 0 ; i < row ; i++)
        for (j = 0 ; j < col ; j++)
            if (arr[i][j] != 0)
            {
                 tuple [col1][0] = i;
                 tuple [col1][1] = j;
                 tuple [col1][2] = arr[i][j];
                 col1++;
            }
    tuple = realloc (tuple, col1*sizeof(int*));
    printf ("Non zero elements are \n");
    printf (" row column element \n");
    for (i = 0 ; i < col1 ; i++)
        printf ("%d %d %d \n", tuple [i][0], tuple [i][1], tuple[i][2]);
    for (i = 0 ; i < col1 ; i++)
        free (tuple[i]);
    for (i = 0 ; i < row ; i++)
        free (arr[i]);
    free (arr);
    free (tuple);
}