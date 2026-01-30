// Header gaurd
#ifndef MY_ML_H_  // header part 
#define MY_ML_H_

// #include <cstdio>
#include <stddef.h>
#include <stdio.h>

// MALLOC Customization 
#ifndef MY_ML_MALLOC
#include <stdlib.h>
#define MY_ML_MALLOC malloc 
#endif 


// ASSERT Customization 
#ifndef MY_ML_ASSERT
#include <assert.h>
#define MY_ML_ASSERT assert 
#endif


// Matrix structure 
typedef struct{
  size_t rows;
  size_t cols;
  float *es;
} Mat; 

Mat mat_alloc(size_t rows, size_t cols);
float dot(Mat m1, Mat m2);
void multi(Mat res, Mat m1, Mat m2);
void sum(Mat res, Mat m1, Mat m2);
void print_mat(Mat m);

#endif


// Implements macro ensures function bodies are compiled once 
// avoids multiple definitions and linker Errors
#ifdef MY_ML_IMPLEMENTATION

#define MAT_POS(m, i, j) (m).es[(i)*(m).cols + (j)]
#define BLOCK 32



// Allocation of matrix in row major order 
Mat mat_alloc(size_t rows, size_t cols)
{
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.es = MY_ML_MALLOC(sizeof(*m.es)*rows*cols);
  MY_ML_ASSERT(m.es!=NULL);
  return m;
}


float dot (Mat m1, Mat m2)
{
  MY_ML_ASSERT (m1.cols == m2.cols && m1.rows == m2.rows);
  float dot = 0;
  for (size_t i = 0; i < m1.rows; ++i)
  {
    for (size_t j = 0 ; j < m1.cols; ++j)
    {
      dot = dot + (MAT_POS(m1, i, j) * MAT_POS(m2, i, j));
    }
  }
  return dot;
}


void multi (Mat res, Mat m1, Mat m2)
{
  MY_ML_ASSERT(m1.cols == m2.rows && m1.rows == res.rows && m2.cols == res.cols);
  for (size_t i = 0; i < res.rows * res.cols; i++)
    res.es[i] = 0.0f;
  size_t M = m1.rows;
  size_t K = m1.cols;
  size_t N = m2.cols;
  for (size_t bi = 0 ; bi < M; bi += BLOCK)
    for (size_t bk = 0; bk < K ; bk += BLOCK)
      for(size_t bj = 0 ; bj < N; bj += BLOCK)
        for (size_t i = bi; i < bi+BLOCK && i < M ; ++i)
          for (size_t k = bk; k < bk + BLOCK && k < K ; ++k){
            float aik = MAT_POS(m1,i,k);
            for (size_t j = bj; j < bj + BLOCK && j < N ; ++j){
              MAT_POS(res,i,j) += aik * MAT_POS(m2, k, j);
            }
          }
}

void sum(Mat res, Mat m1, Mat m2)
{
  MY_ML_ASSERT (m1.cols == m2.cols && m1.rows == m2.rows);
  MY_ML_ASSERT (res.rows == m1.rows && res.cols == m1.cols);
  for (size_t i = 0; i < m1.rows; ++i)
  {
    for (size_t j = 0; j < m1.cols; ++j) {
      MAT_POS(res, i, j) = MAT_POS(m1, i, j) + MAT_POS(m2, i, j);
    }
  }
}





void print_mat (Mat m)
{
  for (size_t i = 0; i < m.rows; ++i)
  {
    for (size_t j = 0; j < m.cols; ++j)
  {
      printf("%f ", MAT_POS(m, i, j));
    }
    printf("\n");
  }
}


#endif // MY_ML_IMPLEMENTATION

