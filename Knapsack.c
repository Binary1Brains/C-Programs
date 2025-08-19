#include <stdio.h>
#include <stdlib.h>

int max (int a, int b)
{
	return (a>b) ? a:b;
}

int knapsack (int W, int * wt, int * val , int n)
{
	int ** dp = (int**) malloc((n+1) * sizeof(int*));
	for (int i = 0; i <= n; i++)
		dp[i] = (int*)calloc (W+1, sizeof(int));
	for (int i = 1; i <= n ; i++)
	{
		for(int w = 0; w <= W; w++)
		{
			if (wt[i-1] <= w)
				dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
			else
				dp[i][w] = dp[i-1][w];
		}
	}
	printf("\nSelected items :\n");
	int w =W;
	for(int i = n; i > 0 && w > 0; i--)
	{
		if(dp[i][w] != dp[i-1][w] )
		{
			printf ("Item %d [weight: %d, value: %d]\n", i-1, wt[i-1], val[i-1]);
			w-=wt[i-1];
		}
	}
	int res = dp[n][W];
	for (int i = 0 ; i <= n; i++)
		free(dp[i]);
	free(dp);
	return res;
}

int main ()
{
	int n, W;
	printf ("Enter number of items ");
	scanf("%d", &n);
	int * wt = (int *) malloc(n* sizeof(int));
	int * val = (int *) malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		printf("Enter weight and values for item %d ", i+1);
		scanf("%d %d", &wt[i], &val[i]);
	}
	printf ("Enter the capacity of Knapsack: ");
	scanf("%d", &W);
	int result = knapsack(W,wt,val,n);
	printf ("\nMaximum value in knapsack = %d\n", result );
	free(wt);
	free(val);
	return 0;
}
