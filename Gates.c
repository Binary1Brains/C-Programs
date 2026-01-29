#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// or gate 
float train [][3] = {
{0,0,0},
{1,0,1},
{0,1,1},
{1,1,1}
};
#define train_count  (sizeof (train)/sizeof(train[0]))

float rand_float()
{
  return (float)rand()/(float)RAND_MAX;
}

float sigmoidf (float x)
{
  return 1.f/(1.f+expf(-x));
}

float mse (float w1 , float w2, float b)
{
  float res = 0.0f;
  for (size_t i = 0 ; i < train_count; i++)
  {
    float x1 = train [i][0];
    float x2 = train [i][1];
    float y = sigmoidf(x1*w1+x2*w2+b);
    float d = y-train[i][2];
    res += d*d;
  }
  res /= train_count;
  return res;
}

int main ()
{
  srand(60);
  float w1 = rand_float ();
  float w2 = rand_float();
  float epsilon = 1e-3;
  float rate = 1e-2;
  float bias = rand_float();
  for (size_t i = 0 ; i < 300000 ; i++){
    printf ("Weights are : w1 = %f, w2 = %f \n", w1,w2);
    float mse1 = mse(w1,w2,bias);
    float dw1 = (mse(w1+epsilon, w2, bias)-mse1)/epsilon;
    float dw2 = (mse(w1, w2+epsilon, bias)-mse1)/epsilon;
    float dbias = (mse (w1,w2, bias+epsilon)-mse1)/epsilon; 
    w1 -= rate*dw1;
    w2 -= rate*dw2;
    bias -= rate*dbias; 
    printf ("Mean squared error is %f with bias %f\n", mse1, bias);
  }
  for (size_t i = 0 ; i < 2; i++)
  {
    for (size_t j = 0 ; j < 2; j++)
    {
      printf ("%zu | %zu = %f\n", i,j,sigmoidf(i*w1+j*w2+bias));
    }
  }
}
