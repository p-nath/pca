#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rows;
  int columns;
  double **data;
} Matrix;

Matrix* CreateNewMatrix(int n, int m);

Matrix* ReadMatrix(char *file_name);

void WriteMatrix(FILE* file_pointer, Matrix* matrix);

Matrix* Transpose(Matrix* matrix);

Matrix* Covariance(Matrix* matrix);

Matrix* Product(Matrix* m1, Matrix* m2);

Matrix* Mean(Matrix* matrix);

void DestroyMatrix(Matrix* matrix);

double GetNorm(Matrix* matrix);

Matrix* GetColumnMatrix(Matrix* matrix, int column_no);

Matrix* MakeColumnMatrix(Matrix* column_matrix, int column_no);

Matrix* GetRowMatrix(Matrix* matrix, int row_no);

Matrix* MakeRowMatrix(Matrix* row_matrix, int row_no);

Matrix* Difference(Matrix* A, Matrix* B);

Matrix* ScalarDivide(Matrix* matrix, double x);

Matrix* GetIdentityMatrix(int x); // x = rows = columns

void CopyMatrix(Matrix* A, Matrix* B); // B is the matrix which is copied to A

void Bidiagonalize(Matrix* A);

#endif