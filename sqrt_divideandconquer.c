#include <stdio.h>
#include <stdlib.h>

int main()
{
    float l, r, num, mid,  sqrt;
    printf("Enter your number: " );
    scanf("%f", &num);
    printf("The number is : %f \n", num);
    l = 0.0; r = num; 
    if (num < 2)
    {
       printf ("The square root is %f\n", num);
       return 0;
    }
    while (l<r)
    {
        mid = (l+r)/2;
        sqrt = mid * mid;
        if (sqrt == num)
        {
            printf ("The square root is %f \n", mid);
            return 0;
        }
        else if(sqrt < num)
        {
            l = mid+1;
            continue;
        }
        else
        {
            r = mid -1;
            continue;
        }
    }

}