#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRAIN_COUNT 4
#define HIDDEN 2

float train[TRAIN_COUNT][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};

float randf()
{
    return (float)rand() / RAND_MAX * 2.0f - 1.0f;
}

float sigmoid(float x) 
{
    return 1.0f / (1.0f + expf(-x));
}

float dsigmoid(float y)
{
    return y * (1 - y);
}

int main()
{
    srand(23);
    float w1[HIDDEN][2];
    float b1[HIDDEN];
    float w2[HIDDEN];
    float b2;            
    for (int i = 0; i < HIDDEN; i++) 
    {
        w1[i][0] = randf();
        w1[i][1] = randf();
        b1[i] = randf();
        w2[i] = randf();
    }
    b2 = randf();
    float rate = 0.5f;
    for (int epoch = 0; epoch < 10000; epoch++)
    {
        float total_loss = 0.0f;
        for (int t = 0; t < TRAIN_COUNT; t++)
        {
            float x1 = train[t][0];
            float x2 = train[t][1];
            float y_true = train[t][2];
            float h[HIDDEN];
            for (int i = 0; i < HIDDEN; i++)
            {
                float z = x1 * w1[i][0] + x2 * w1[i][1] + b1[i];
                h[i] = sigmoid(z);
            }
            float y_pred = sigmoid(h[0] * w2[0] + h[1] * w2[1] + b2);
            float error = y_pred - y_true;
            total_loss += error * error;
            float d_y = 2 * error * dsigmoid(y_pred); 
            float d_w2[HIDDEN];
            for (int i = 0; i < HIDDEN; i++)
            {
                d_w2[i] = d_y * h[i];
            }
            float d_b2 = d_y;
            float d_h[HIDDEN];
            for (int i = 0; i < HIDDEN; i++)
            {
                d_h[i] = d_y * w2[i] * dsigmoid(h[i]);
            }

            float d_w1[HIDDEN][2];
            float d_b1[HIDDEN];
            for (int i = 0; i < HIDDEN; i++)
            {
                d_w1[i][0] = d_h[i] * x1;
                d_w1[i][1] = d_h[i] * x2;
                d_b1[i] = d_h[i];
            }
            for (int i = 0; i < HIDDEN; i++)
            {
                w1[i][0] -= rate * d_w1[i][0];
                w1[i][1] -= rate * d_w1[i][1];
                b1[i] -= rate * d_b1[i];
                w2[i] -= rate * d_w2[i];
            }
            b2 -= rate * d_b2;
        }
        total_loss /= TRAIN_COUNT;
        if (epoch % 1000 == 0)
            printf("Epoch %d\tLoss: %.6f\n", epoch, total_loss);
    }
    printf("\nTrained Results:\n");
    for (int t = 0; t < TRAIN_COUNT; t++)
    {
        float x1 = train[t][0];
        float x2 = train[t][1];
        float h[HIDDEN];
        for (int i = 0; i < HIDDEN; i++)
        {
            h[i] = sigmoid(x1 * w1[i][0] + x2 * w1[i][1] + b1[i]);
        }
        float y_pred = sigmoid(h[0] * w2[0] + h[1] * w2[1] + b2);
        printf("%.0f | %.0f = %.3f\n", x1, x2, y_pred);
    }
    return 0;
}
