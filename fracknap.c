#include <stdio.h>
#include <stdlib.h>

typedef struct Item
{
    int w;
    int v;
    float r;
} Item;

void sort(Item *items, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (items[j].r < items[j + 1].r)
            {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

void knapsack(int n, int W, Item *item)
{
    sort(item, n);
    float res = 0.0;
    printf (" \nSelected Items:\n");
    for (int i = 0; i < n && W > 0; i++)
    {
        if (item[i].w <= W)
        {
            W -= item[i].w;
            res += item[i].v;
            printf (" Item %d: amount: 100%% [weight %d, value %d]\n", i + 1, item[i].w, item[i].v);
        }
        else
        {
            float frac = (float)W / item[i].w;
            res += item[i].v * frac;
            printf (" Item %d: amount: %.2f%% [weight %d, value %d]\n", i + 1, frac * 100, item[i].w, item[i].v);
            W = 0;
        }
    }
    printf (" \nMaximum value in knapsack = %.2f\n", res);
}

int main()
{
    int n, W;
    printf (" Enter number of items: ");
    scanf ("%d", &n);
    Item *item = (Item *)malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++)
    {
        printf (" Enter weight and value for item %d: ", i + 1);
        scanf ("%d %d", &item[i].w, &item[i].v);
        item[i].r = (float)item[i].v / item[i].w;
    }
    printf (" Enter the capacity of knapsack: ");
    scanf ("%d", &W);
    knapsack(n, W, item);
    free(item);
    return 0;
}
