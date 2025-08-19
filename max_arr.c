//maximum subarray 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct crossing_point
{
	int max_left;
	int max_right;
	int sum;
} crossing_point;

crossing_point * Find_max_cross_point (int * arr, int low, int mid, int high)
{
	int left_sum = INT_MIN, right_sum = INT_MIN;
	crossing_point * cp = (crossing_point *) malloc(sizeof(crossing_point));
	int sum = 0;
	for (int i = mid ; i >= low ; i--)
	{
		sum = sum + arr[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			cp->max_left = i;
		}
	}
	sum = 0;
	for (int i = mid+1; i <= high ; i++)
	{
		sum = sum + arr[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			cp->max_right = i;
		}
	}
	cp->sum = right_sum + left_sum;
	return cp;
}

crossing_point * Find_maximum_subarray (int * arr, int low, int high)
{
	if (high == low)
	{
	        crossing_point * rescp = (crossing_point *) malloc(sizeof(crossing_point));
		rescp->max_left = low;
		rescp->max_right = high;
		rescp->sum = arr[low];
		return rescp;
	}
	else
	{
	        int mid = (int)((low + high) / 2);
		crossing_point * rescpleft = Find_maximum_subarray(arr,low,mid);
                crossing_point * rescpright = Find_maximum_subarray(arr,mid+1,high);
                crossing_point * cross = Find_max_cross_point (arr, low, mid, high);
		if (rescpleft->sum >= rescpright->sum && rescpleft->sum >= cross->sum)
		{
			free(rescpright);
			free(cross);
			return rescpleft;
		}
		else if(rescpright->sum >= rescpleft->sum && rescpright->sum >= cross->sum)
		{
			free(rescpleft);
			free(cross);
			return rescpright;
		}
		else
		{
			free(rescpright);
			free(rescpleft);
			return cross;
		}
	}
}

int main ()
{
	int n ;
	printf ("Enter your size of the array : ");
	scanf ("%d", &n);
	int * arr = (int*) malloc (n*sizeof(int));
	printf("Enter array elements : " );
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	crossing_point * p = Find_maximum_subarray(arr, 0, n-1);
	printf ("Crossing points is %d to %d with maximum sum %d \n ", p->max_left, p->max_right, p->sum);
	printf(" The Elements are ");
	for (int i = p->max_left; i <= p->max_right; i++)
		printf("%d ", arr[i]);
	printf("\n");
	free (p);
	return 0;
}
