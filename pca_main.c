#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#define line printf("\n");

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

  /*Matrix *A = NULL;
  A = ReadMatrix(input_filename);
  //WriteMatrix(fout, A);

  Matrix* U = NULL, *V_t = NULL;
  Bidiagonalize(A, U, V_t);
  WriteMatrix(fout, A);

  Matrix* A_t = Transpose(A);
  Matrix* B = Product(A_t,A);*/

  Matrix* B = ReadMatrix(input_filename);
  WriteMatrix(stdout, B); line

  Matrix *Q = CreateNewMatrix(B->rows, B->columns), *R = CreateNewMatrix(B->rows, B->columns);
  QR_Decomposition(B, Q, R);

  WriteMatrix(stdout,Q);line
  WriteMatrix(stdout, R);line
  WriteMatrix(stdout, Product(Q, R));



  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }
  return 0;
}
