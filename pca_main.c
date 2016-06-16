#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#define line printf("\n");
#define test printf("%d\n",__LINE__);
#define FALSE 0
#define TRUE 1

int parse_args(int argc, char** argv, char **input_filename, char **output_filename) {
  if (argc >= 2){
    *input_filename = argv[1];
    if (argc == 3)
      *output_filename = argv[2];
    return TRUE;
  }
  else {
    printf("%s <input_filename> <output_filename>\n", argv[0]);
    return FALSE;
  }
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  if (!parse_args(argc, argv, &input_filename, &output_filename))  exit(-1);
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;

  Matrix *A = NULL;
  A = ReadMatrix(input_filename);
  WriteMatrix(stdout, A); line

  Matrix *_U = CreateNewMatrix(A->rows, A->rows), *_V = CreateNewMatrix(A->columns, A->columns);
  Bidiagonalize(A, _U, _V);
  printf("Bidiagonal Matrix: \n");
  WriteMatrix(stdout, A); line
  printf("_U: \n");
  WriteMatrix(stdout, _U); line
  printf("_V: \n");
  WriteMatrix(stdout, _V); line

  Matrix* A_t = Transpose(A);
  Matrix* B = Product(A_t,A);

  printf("symmetric square matrix(B*B_t) : \n");
  WriteMatrix(stdout, B); line

  Matrix *Q = CreateNewMatrix(B->rows, B->rows), *Q_t = CreateNewMatrix(B->rows, B->rows), *R = CreateNewMatrix(B->rows, B->columns);
  QR_Converge(B, Q, Q_t, R);

  printf("after QR covergence (actually the SVD of B*B_t): \n");
  WriteMatrix(stdout, Q);line
  WriteMatrix(stdout, R);line
  WriteMatrix(stdout, Q_t);line


  DestroyMatrix(B);
  DestroyMatrix(Q);
  DestroyMatrix(Q_t);
  DestroyMatrix(R);
  DestroyMatrix(_U);
  DestroyMatrix(_V);
  DestroyMatrix(A);

  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }
  return 0;
}
