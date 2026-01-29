// THEORY
// AS NAND OPERATOR IS WRITTEN AS NAND(A,B) = (A.B)' CONTAINING AND(.) AND NOT(')
// AS A SINGLE PERCEPTRON CAN EMULATE A SINGLE OPERATOR THIS IMPLIES 
// N PERCEPTRON CAN SIMULATE ANY FUNCTION IN |Rn Universal approximation theorem : A feedforward neural 
// network with one hidden layer and a finite number of neurons can approximate any continuous 
// real-valued function on compact subsets of |Rn given enough neurons and the right activation 
// function like sigmoid or ReLU 
// A single perceptron can compute z = w^T.x + b then applies an activation function y = Phi(z) 
// [w is a column vector ; x is a column vector dot product results in a scalar]
// w^T.x + b = 0 is a hyperplane. The perceptron classifies or regresses based on which side of the 
// hyperplane a point lies so a single perceptron can only model linearly separable sets.
// therefore AND, OR and NOT are solved by a single Perceptron. Bias of the  equation is necessary so 
// that the hyperplane can move freely and doesn't gets restricted to the origin of the space.
// Stacking perceptron : Composing of multiple affine (linear and bias) transformation one after the 
// other where output of one layer becomes the input of the second one 
// => y = W2(W1.x + b1) + b2 ===> y = (W2.W1).x + (W2.b1 + b2) wihout nonlinearity collapses into a 
// single layer adding no expressive power
// Stacking activation : This inserts a nonlinearity h = sigmoid (W1.x + b1) ; y = W2.h + b2 the 
// composition is non linear 
// Therefore Stacking perceptron : applies linear projection : drawing linear boundaries in space
// Stacking activation : nonlinear wrapping of space : bending the space 
// Here :
//        Stacking linear layers : y = W2(W1.x) --> y = W.x  
//        Activation introduces non linearity : sigmoid (x) = 1/(1+e^(-x)) {Bounded in (0,1), smooth 
//        and differentiable } resulting in gradient based learning and probabilistic interpretations
// XOR (x1 , x2) = (x1.x2')+(x1'.x2) each hidden neuron learns a separate linear region applies a non 
// linear transformation the output neuron combines those regions linearly 
// VERY MATHEMATICAL DESCRIPTION :
//        A model : f(x;theta)
//        A loss function : L(y,y_pred)
//        An optimization rule : theta <- theta - n Grad_theta (L)
// here loss function is MSE = (y_pred - y)^2 results in smooth convergence penalizing large errors 
// quadratically 
// Backpropagation is the chain rule applied to nested function L(y(sigmoid(z(w))))
// dL/dw = dL/dy . dy/dz . dz/dw

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRAIN_COUNT 4
#define HIDDEN 2

float train [TRAIN_COUNT][3]={
{0,0,1},
{0,1,1},
{1,0,1},
{1,1,0}};

float randf() {
  return (float)rand() / RAND_MAX * 2.0f - 1.0f;
}

float sigmoid (float x){
  return 1.0f / (1.0f + expf(-x));
}

float dsigmoid (float y){ // gradient collapse
  return y*(1-y);
}

int main (){
  srand (2);
  float w1[HIDDEN][2];
  float b1[HIDDEN];
  float w2[HIDDEN];
  float b2;

  for (int i = 0 ; i < HIDDEN ; i++){
    w1[i][0] = randf();
    w1[i][1] = randf();
    b1[i] = randf();
    w2[i] =randf();
  }
  b2 = randf();
  float rate = 0.5f;
  for (int epoch = 0  ; epoch < 10000; epoch++){
    float total_loss =  0.0f;
    for (int t = 0;  t < TRAIN_COUNT; t++){
      float x1 = train[t][0];
      float x2 = train[t][1];
      float y_actual = train[t][2];

      //forward passing 
      float h[HIDDEN];
      for (int i = 0; i<HIDDEN;i++){
        float z = x1*w1[i][0]  + x2 * w1[i][1] + b1[i];
        h[i] = sigmoid(z);
      }
      float y_pred = sigmoid(h[0] * w2[0] + h[1] * w2[1] + b2);

      // prediction loss 
      float error = y_pred - y_actual;
      total_loss += error * error;

      // backward pass 
      float d_y = 2* error * dsigmoid(y_pred);
      float d_w2[HIDDEN];
      for (int i = 0; i < HIDDEN; i++){
        d_w2[i] = d_y * h[i];
      }
      float d_b2 = d_y;
      float d_h[HIDDEN];
      for (int i = 0 ; i < HIDDEN; i++){
        d_h[i] = d_y * w2[i] * dsigmoid(h[i]);
      }
      float d_w1[HIDDEN][2];
      float d_b1[HIDDEN];
      for (int i = 0 ; i < HIDDEN; i++){
        d_w1[i][0] = d_h[i] * x1;
        d_w1[i][1] = d_h[i] * x2;
        d_b1[i] = d_h[i];
      }
      for ( int i = 0; i < HIDDEN; i++){
        w1[i][0] -= rate * d_w1[i][0];
        w1[i][1] -= rate * d_w1[i][1];
        b1[i] -= rate * d_b1[i];
        w2[i] -= rate * d_w2[i];
      }
      b2 -= rate * d_b2;
    }
    total_loss /= TRAIN_COUNT;
    if (epoch % 1000 == 0)
      printf ("Epoch %d\tLoss %.6f\n", epoch, total_loss);
  }
  printf ("\n Trained Result\n");
  for(int t = 0; t< TRAIN_COUNT;t++){
    float x1 = train[t][0];
    float x2 = train[t][1];
    float h[HIDDEN];
    for (int i = 0 ; i < HIDDEN; i++){
      h[i] = sigmoid(x1*w1[i][0] + x2*w1[i][1] + b1[i]);
    }
    float y_pred = sigmoid(h[0] * w2[0] + h[1]* w2[1] + b2);
    printf ("%.0f XOR %.0f = %.3f\n", x1, x2, y_pred);
  }
  return 0;
}

// Forward pass : The forward pass is the evaluation of the model output by function composition from input to output 
// For a single neuron z = w^T.x + b ; y_pred = sigmoid(z). For a multi-layer network 
// a(0) = x ; z(l) = W(l)a(l-1) + b(l) ; a(l) = sigmoid(z(l)) => y_pred = a(l) 
// The forward pass computes predictions only machine doesn't retains knowledge 
// Loss evaluation (bridge step) : 
// Backward pass : The backward pass computes gradients of the loss with respect to 
// parameters using the chain rule 
