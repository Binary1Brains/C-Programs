#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float train[][2] = {{0,0}, {1,2}, {2,4}, {3,6}, {4,8}};
#define train_count (sizeof(train)/sizeof(train[0]))


float rand_float()
{
  return (float)rand()/(float)RAND_MAX*10.0f;
}

float cost (float w, float biases)
{
  float res = 0.0f;
  for (size_t i = 0 ; i < train_count; i++)
  {
      float x = train[i][0];
      float y = x*w+biases;
      float mse = pow((y - train[i][1]),2);
      res += mse;
      printf ("Predicted %f Actual %f\n", y, train[i][1]);
  }
  res /= train_count;
  return res;
}


int main()
{
  // y = x*2
  srand(7);
  float w = 1.0f; // or use w = rand_float();
  float biases = rand_float();
  float epsilon = 1e-3;
  float rate = 1e-3;
  printf ("%f\n", w);
  printf ("%f\n", cost (w,biases));
  for (size_t i = 0; i < 4999; i++)
  {
    float dcost = (cost(w+epsilon, biases) - cost (w, biases))/epsilon;
    float dbiases = (cost(w,biases+epsilon)- cost (w,biases))/epsilon;
    w -= rate * dcost;
    biases -= rate * dbiases;
    printf ("Mean squared error %f , Weight %f, Biases %f\n", cost(w,biases), w, biases);
  }
  return 0;
  printf ("Final weight approximation %f with bias %f \n", w, biases);
}
