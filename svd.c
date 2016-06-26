#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"
#include "svd.h"

Matrix* assert_matrix(Matrix* A) {
  assert(A->rows == A->columns);
  return A;
}

//for square symmetric matrices / covariance matrices
void QR_Decomposition(Matrix* B, Matrix* Q, Matrix* R) {
  assert_matrix(B);
  double t, r, c, s;
  Matrix* P = NULL; 
  Matrix* Q_temp = NULL;
  Matrix* G_t = NULL;
  Matrix* G = CreateNewMatrix(B->rows, B->columns);
  //Givens rotation
  CopyMatrix(R, B);
  for (int count = 0; count < B->rows-1; count++) {
    t = R->data[count+1][count];
    r = sqrt(pow(R->data[count][count], 2) + pow(t, 2));
    c = R->data[count][count]/r;
    s = t/r;
    for (int i = 0; i < G->rows; i++) {
      for (int j = 0; j < G->columns; j++) {
        if ((i == count && j == count) || (i == count+1 && j == count+1))  G->data[i][j] = c;
        else if (i == count+1 && j == count)  G->data[i][j] = -1*s;
        else if (i == count && j == count+1)  G->data[i][j] = s;
        else if (i == j)  G->data[i][j] = 1;
        else  G->data[i][j] = 0;
      }
    }
    P = Product(G, R);
    CopyMatrix(R, P);
    G_t = Transpose(G);
    if (count == 0) CopyMatrix(Q, G_t);
    else {
      Q_temp = Product(Q, G_t);
      CopyMatrix(Q, Q_temp);
      DestroyMatrix(Q_temp);
    }
    DestroyMatrix(G_t);
    DestroyMatrix(P);
  }
  DestroyMatrix(G);
}

void QR_Converge(Matrix* B, Matrix* Q, Matrix* Q_t, Matrix* R, int hyper_parameter) {
  QR_Decomposition(B, Q, R);
  Matrix* A2 = Product(R, Q);
  Matrix* Q_temp = CreateNewMatrix(Q->rows, Q->columns);
  Matrix* Q_t_temp = CreateNewMatrix(Q->columns, Q->rows);
  Matrix* Q_product = NULL, *Q_t_product = NULL;
  Matrix* _Q_t = Transpose(Q);

  CopyMatrix(Q_t, _Q_t);
  DestroyMatrix(_Q_t);
  CopyMatrix(Q_temp, Q);
  CopyMatrix(Q_t_temp, Q_t);

  for(int i = 0; i < hyper_parameter; i++) {
    QR_Decomposition(A2, Q, R);
    A2 = Product(R, Q);
    Q_product = Product(Q_temp, Q);
    _Q_t = Transpose(Q);
    CopyMatrix(Q_t, _Q_t);
    Q_t_product = Product(Q_t, Q_t_temp);
    CopyMatrix(Q_temp, Q_product);
    CopyMatrix(Q_t_temp, Q_t_product);
    DestroyMatrix(_Q_t);
  }
  CopyMatrix(Q, Q_product);
  CopyMatrix(Q_t, Q_t_product);
  DestroyMatrix(Q_product);
  DestroyMatrix(Q_t_product);

  
  DestroyMatrix(A2);
  DestroyMatrix(Q_temp);
  DestroyMatrix(Q_t_temp);

}

void SVD(Matrix* A, Matrix* U, Matrix* Z, Matrix* V, int hyper_parameter) {
  Matrix* covariance = Covariance(A);
  printf("The covariance matrix:\n");
  WriteMatrix(stdout, covariance);
  printf("\n");
  QR_Converge(covariance, U, V, Z, hyper_parameter);
  DestroyMatrix(covariance);
}

Matrix* CreateProjectionMatrix(Matrix* U, int initial_dimensions, int final_dimensions) {
  Matrix* W = CreateNewMatrix(initial_dimensions, final_dimensions);
  CopyMatrix(W, U);
  return W;
}



