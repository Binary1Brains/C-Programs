#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct point {
    int max_left;
    int max_right;
    int max_cross;
} point;

point* Max_crossing_subarray(int* A, int low, int mid, int high)
{
    int left_sum = INT_MIN, sum = 0, right_sum = INT_MIN;
    point* res = (point*)malloc(sizeof(point));
    for (int i = mid; i >= low; i--)
    {
        sum = sum + A[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            res->max_left = i;
        }
    }
    sum = 0;
    for (int i = mid + 1; i <= high; i++)
    {
        sum = sum + A[i];
        if (sum > right_sum)
        {
            right_sum = sum;
            res->max_right = i;
        }
    }
    res->max_cross = left_sum + right_sum;
    return res;
}

point * Maximum_subarray(int* A, int low, int high)
{
    if (low == high)
    {
        point* res = (point*)malloc(sizeof(point));
        res->max_left = low;
        res->max_right = high;
        res->max_cross = A[low];
        return res;
    }
    else 
    {
        int mid = (low + high) / 2;
        point* left = Maximum_subarray(A, low, mid);
        point* right = Maximum_subarray(A, mid + 1, high);
        point* cross = Max_crossing_subarray(A, low, mid, high);
        if ((left->max_cross >= right->max_cross) && (left->max_cross >= cross->max_cross)) 
        {
            free(right);
            free(cross);
            return left;
        }
        else if ((right->max_cross >= left->max_cross) && (right->max_cross >= cross->max_cross)) 
        {
            free(left);
            free(cross);
            return right;
        } 
        else
        {
            free(left);
            free(right);
            return cross;
        }
    }
}

int main() 
{
    int* arr;
    int i, size;
    printf("Enter size of the array: ");
    scanf("%d", &size);
    arr = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) 
    {
        printf("Enter element %d of the array: ", i + 1);
        scanf("%d", &arr[i]);
    }
    point* result = Maximum_subarray(arr, 0, size - 1);
    printf("Maximum Subarray is from index %d to %d with sum %d\n", result->max_left, result->max_right, result->max_cross);
    printf("Subarray: ");
    for (i = result->max_left; i <= result->max_right; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(result);
    free(arr);

    return 0;
}
