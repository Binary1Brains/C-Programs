//quick sort
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int partitioning (int * arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1, temp;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			SWAP(arr[i], arr[j], temp);
		}
	}
	SWAP(arr[i+1], arr[high], temp);
	return i+1;
}

void quicksort (int * arr, int low, int high)
{
	if(low < high)
	{
		int partition_in = partitioning(arr, low, high);
		quicksort(arr,low,partition_in-1);
		quicksort(arr,partition_in+1,high);
	}
}

int main ()
{
	int n;
	printf("Enter size of array ");
	scanf("%d", &n);
	int * arr= (int*) malloc (n*sizeof(int));
	printf("Enter your elements of the array ");
	for (int i = 0; i < n ; i++)
		scanf("%d", (arr+i));
	quicksort(arr,0,n-1);
	for(int i = 0; i < n ; i++)
		printf("%d ", *(arr+i));
	printf("\n");
	free(arr);
}
