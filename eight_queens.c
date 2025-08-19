//eight _ queens problem 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int * board;
int N;
int solcount = 0;

bool is_safe (int row, int col)
{
	for (int i = 0; i < row ; i++)
	{
		if (board[i] == col || board[i] - i == col -row || board[i] + i == col + row)
			return false;
	}
	return true;
}

void print_sol ()
{
	solcount++;
	printf( "Solution : %d\n", solcount);
	for (int i = 0; i < N ; i++)
	{
		for (int j = 0; j < N; j++)
			printf(board[i] == j ? "Q " : ". ");
		printf("\n");
	}
	printf("Positional array [");
	for (int i = 0; i < N; i++)
	{
		printf("%d", board[i]);
		if (i<N-1)
			printf( ", ");
	}
	printf("]\n\n");
}

void n_queens (int row )
{
	if (row == N)
	{
		print_sol ();
		return;
	}
	for (int col = 0; col < N; col++)
	{
		if (is_safe(row,col))
		{
			board[row] = col;
			n_queens (row + 1 );
		}
	}
}

int main ()
{
	printf ("Enter size of board ");
	scanf ("%d", &N);
	board = (int *) malloc (N* sizeof (int));
	n_queens (0);
	if (solcount == 0)
		printf("No solutions exists ");
	else
		printf("Total solution is : %d\n", solcount);
	free (board);
	return 0;
}
