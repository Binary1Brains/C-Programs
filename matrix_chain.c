// Matrix Chain multiplication

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct table
{
	int ** m;
	int ** s;
}table;

table * Matrix_chain_order (int * p, int n )
{
	table * t = (table *) malloc (sizeof(table));
	t->m = (int **) malloc ((n+1) * sizeof (int *));
	t->s = (int **) malloc ((n+1) * sizeof (int *));
	for ( int i = 0; i <= n; i++)
	{
		t->m[i] = (int*) malloc ((n+1) * sizeof(int));
		t->s[i] = (int*) malloc ((n+1) * sizeof(int));
	}
	for (int i = 1; i <= n; i++)
		t->m[i][i] = 0;
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= (n-l+1); i++)
		{
			int j = i+l-1;
			t->m[i][j] = INT_MAX;
			for (int k = i; k <= (j-1); k++)
			{
				int q = t->m[i][k] + t->m[k+1][j] + (p[i-1]*p[k]*p[j]);
				if (q < t->m[i][j])
				{
					t->m[i][j] = q;
					t->s[i][j] = k;
				}
			}
		}
	}
	return t;
}

void print_mat (int ** m, int n)
{
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= n; j++) 
		{
			if (i > j)
				printf("   - ");
			else
				printf("%4d ", m[i][j]);
		}
		printf("\n");
	}
}

void print_optimal_paren (int ** s, int i , int j)
{
	if (i == j)
		printf ("A[%d]",i);
	else
	{
		printf ("(");
		print_optimal_paren (s, i, s[i][j]);
		print_optimal_paren (s, s[i][j] + 1, j);
		printf(")");
	}
}

int main ()
{
	int n ;
	printf ("Enter number of matrices to be multiplied : " );
	scanf("%d", &n);
	int * p = (int*) malloc((n+1) * sizeof (int));
	for (int i = 0; i <= n; i++)
	{
    		printf("Enter p[%d]: ", i);
    		scanf("%d", &p[i]);
	}
	table * res = Matrix_chain_order (p, n);
	printf ("Minimum cost matrix \n");
	print_mat (res->m, n);
	printf ("Split point matrix \n");
	print_mat (res->s, n);
	printf ("Parenthesis visual ");
	print_optimal_paren (res->s, 1, n);
	printf("\n");
	for (int i = 0; i <= n; i++) 
	{
		free(res->m[i]);
		free(res->s[i]);
	}
	free(res->m);
	free(res->s);
	free(res);
	free(p);
	return 0;
}
