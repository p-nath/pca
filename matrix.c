#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#define line printf("\n");

Matrix* CreateNewMatrix(int n, int m) {
  Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
  matrix->rows = n;
  matrix->columns = m;
  matrix->data = (double**)malloc(sizeof(double)*n);
  for (int i = 0; i < n; i++){
    matrix->data[i] = (double*)malloc(sizeof(double)*m);
  }
  return matrix;
}


void DestroyMatrix(Matrix* matrix) {
  for (int n = 0; n < matrix->rows; n++) {
    free(matrix->data[n]);
  }
  free(matrix);
}

Matrix* ReadMatrix(char *file_name) {
  double x;
  char flag;
  int r, c;
  FILE *fin;
  fin = fopen(file_name, "r");
  fscanf(fin, "%d", &r);
  fseek(fin, 1,SEEK_CUR);
  fscanf(fin, "%d", &c);
  fseek(fin, 1,SEEK_CUR);
  Matrix* matrix = CreateNewMatrix(r, c);
  for (int n = 0; n < matrix->rows; n++) {
    flag = 0;
    for (int m = 0; m < matrix->columns; m++) {
      fscanf(fin, "%lf", &x);
      fseek(fin, 1, SEEK_CUR);
      matrix->data[n][m] = x;
    }
  }
  fclose(fin);
  printf("Matrix read from %s\n", file_name);
  return matrix;
}

void WriteMatrix(FILE* file_pointer, Matrix* matrix) {
  for (int n = 0; n < matrix->rows; n++) {
    for (int m = 0; m < matrix->columns; m++) {
      if (m == matrix->columns - 1)  fprintf(file_pointer, "%lf\n", matrix->data[n][m]);
      else  fprintf(file_pointer, "%lf ",matrix->data[n][m]);
    }
  }
}

Matrix* Transpose(Matrix* matrix) {
  Matrix* transpose;
  transpose = CreateNewMatrix(matrix->columns, matrix->rows);
  for (int n = 0; n < transpose->rows; n++) {
    for (int m = 0; m < transpose->columns; m++) {
      transpose->data[n][m] = matrix->data[m][n];
    }
  }
  return transpose;
}

Matrix* Product(Matrix* m1, Matrix* m2) {
  if (m1->columns != m2->rows) {
    printf("Not Possible\n");
    return NULL;
  }
  Matrix* res = CreateNewMatrix(m1->rows, m2->columns);
  double element;
  for (int n = 0; n < res->rows; n++) {
    for (int m = 0; m < res->columns; m++) {
      element = 0;
      for(int i = 0; i < m2->rows; i++) {
        element += m1->data[n][i]*m2->data[i][m];
      }
      res->data[n][m] = element;
    }
  }
  return res;
}

Matrix* Mean(Matrix* matrix) {
  double* column_avg = (double*)malloc(sizeof(double)*matrix->columns);
  double sum = 0;
  Matrix* mean = CreateNewMatrix(matrix->rows, matrix->columns);
  for (int n = 0; n < matrix->columns; n++) {
    sum = 0;
    for (int m = 0; m < matrix->rows; m++) {
      sum += matrix->data[m][n];
    }
    column_avg[n] = sum/mean->rows;
  }
  for (int m = 0; m < mean->columns; m++) {
    for (int n = 0; n < mean->rows; n++) {
      mean->data[n][m] = matrix->data[n][m] - column_avg[m];
    }
  }
  return mean;
}

Matrix* Covariance(Matrix* matrix) {
  Matrix* covariance = CreateNewMatrix(matrix->columns, matrix->columns);
  Matrix* mean = Mean(matrix);
  Matrix* transpose = Transpose(mean);
  Matrix* product = Product(transpose, mean);

  for (int n = 0; n < covariance->rows; n++) {
    for (int m = 0; m < covariance->columns; m++) {
      covariance->data[n][m]= product->data[n][m]/(matrix->rows -1);
    }
  }
  DestroyMatrix(mean);
  DestroyMatrix(transpose);
  DestroyMatrix(product);
  return covariance;
}


double GetNorm(Matrix* matrix) {
  double norm, sum_of_squares = 0;
  for (int n = 0; n < matrix->rows; n++)
    for (int m = 0; m < matrix->columns; m++) {
      sum_of_squares += pow(matrix->data[n][m], 2);
    }
  norm = sqrt(sum_of_squares);
  return norm;
}

Matrix* GetColumnMatrix(Matrix* matrix, int column_no) {
  Matrix* column_matrix = CreateNewMatrix(matrix->rows, 1);
  for (int n = 0; n < column_matrix->rows; n++) {
    column_matrix->data[n][0] = matrix->data[n][column_no];
  }
  return column_matrix;
}

Matrix* MakeColumnMatrix(Matrix* column_matrix, int column_no) {
  Matrix* new_matrix = CreateNewMatrix(column_matrix->rows, 1);
  if (column_no == 0){
    for (int n = 0; n < new_matrix->rows; n++) {
      if (n == column_no)  
        new_matrix->data[n][0] = GetNorm(column_matrix);
      else new_matrix->data[n][0] = 0;
    }
  }
  else {
    for (int n = 0; n < new_matrix->rows; n++) {
      if (n < column_no)  
        new_matrix->data[n][0] = column_matrix->data[column_no-1][n];
      else if (n == column_no) {
        double norm = GetNorm(column_matrix);
        double value = sqrt(pow(norm, 2) - pow(column_matrix->data[n-1][0],2));
        new_matrix->data[n][0] = value;
      }
      else new_matrix->data[n][0] = 0;
    }
  }
  return new_matrix;
}


Matrix* GetRowMatrix(Matrix* matrix, int row_no) {
  Matrix* row_matrix = CreateNewMatrix(1, matrix->columns);
  for (int m = 0; m < row_matrix->columns; m++) {
    row_matrix->data[0][m] = matrix->data[row_no][m];
  }
  return row_matrix;
}

Matrix* MakeRowMatrix(Matrix* row_matrix, int row_no) {
  Matrix* new_matrix = CreateNewMatrix(1, row_matrix->columns);
  for (int m = 0; m < new_matrix->columns; m++) {
    if (m <= row_no)  
      new_matrix->data[0][m] = row_matrix->data[0][m];
    else if (m == row_no +1) {
      double norm = GetNorm(row_matrix);
      double value = sqrt(pow(norm, 2) - pow(row_matrix->data[0][m-1],2));
      new_matrix->data[0][m] = value;
    }
    else new_matrix->data[0][m] = 0;

  }
  return new_matrix;
}

Matrix* Difference(Matrix* A, Matrix* B) {
  if (A->rows != B->rows || A->columns != B->columns)  return NULL;
  Matrix* diff = CreateNewMatrix(A->rows, A->columns);
  for (int n = 0; n < diff->rows; n++) {
    for (int m = 0; m < diff->columns; m++) {
      diff->data[n][m] = A->data[n][m] - B->data[n][m];
    }
  }
  return diff;
}

Matrix* ScalarDivide(Matrix* matrix, double x) {
  Matrix* div = CreateNewMatrix(matrix->rows, matrix->columns);
  for (int n = 0; n < div->rows; n++) {
    for (int m = 0; m < div->columns; m++) {
      div->data[n][m] = matrix->data[n][m]/x;
    }
  }
  return div;
}

Matrix* GetIdentityMatrix(int x) {
  Matrix* I = CreateNewMatrix(x, x);
  for (int n = 0; n < I->rows; n++) {
    for (int m = 0; m < I->columns; m++) {
      if (n == m)  I->data[n][m] = 1;
      else  I->data[n][m] = 0;
    }
  }
  return I;
}

void CopyMatrix(Matrix* A, Matrix* B) {
  if (A->rows != B->rows || A->columns != B->columns)  return;
  for (int n = 0; n < A->rows; n++) {
    for (int m = 0; m < A->columns; m++) {
      A->data[n][m] = B->data[n][m];
    }
  }
}

void Bidiagonalize(Matrix* A) {
  int m = 0, n = 0;
  Matrix *x, *y, *z, *w, *w_t, *I, *product, *product2, *P, *final;
  while (1){
    if (m == A->rows - 1 && n == A->columns - 2)  break;
    if (m < A->rows - 1) {
      I = GetIdentityMatrix(A->rows);
      x = GetColumnMatrix(A, m);
      //WriteMatrix(stdout, x);
      y = MakeColumnMatrix(x, m);
      //WriteMatrix(stdout, y);
      z = Difference(x, y);
      w = ScalarDivide(z, GetNorm(z));
      w_t = Transpose(w);
      product = Product(w, w_t);
      //WriteMatrix(stdout, product);
      product2 = ScalarDivide(product, 0.5);
      P = Difference(I, product2);
      final = Product(P, A);
      CopyMatrix(A, final);
      m++;
      DestroyMatrix(I);
      DestroyMatrix(x);
      DestroyMatrix(y);
      DestroyMatrix(z);
      DestroyMatrix(w);
      DestroyMatrix(product);
      DestroyMatrix(product2);
      DestroyMatrix(P);
      DestroyMatrix(final);
      //WriteMatrix(stdout, A);
    }
    WriteMatrix(stdout, A);line
    if (n < A->columns - 2) {
      I = GetIdentityMatrix(A->columns);
      x = GetRowMatrix(A, n); 
      y = MakeRowMatrix(x, n); 
      z = Difference(x, y); 
      w = ScalarDivide(z, GetNorm(z));
      w_t = Transpose(w);
      product = Product(w_t, w);
      product2 = ScalarDivide(product, 0.5);
      P = Difference(I, product2);
      final = Product(A, P);
      CopyMatrix(A, final);
      n++;
      DestroyMatrix(I);
      DestroyMatrix(x);
      DestroyMatrix(y);
      DestroyMatrix(z);
      DestroyMatrix(w);
      DestroyMatrix(product);
      DestroyMatrix(product2);
      DestroyMatrix(P);
      DestroyMatrix(final);
      //WriteMatrix(stdout, A);
    }
    WriteMatrix(stdout, A); line
  }
  WriteMatrix(stdout, A);
}