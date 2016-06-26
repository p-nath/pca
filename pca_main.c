#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "svd.h"

#define FALSE 0
#define TRUE 1

int parse_args(int argc, char** argv, char **input_filename, 
                  char **output_filename, int* hyper_parameter) {
  if (argc >= 2){
    *input_filename = argv[1];
    if (argc >= 3){
      *output_filename = argv[2];
      if (argc == 4)
        *hyper_parameter = atoi(argv[3]);
    }
    return TRUE;
  }
  else {
    printf("%s <input_filename> <output_filename> <hyper_parameter>\n", argv[0]);
    return FALSE;
  }
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  int hyper_parameter = 0;
  if (!parse_args(argc, argv, &input_filename, &output_filename, &hyper_parameter))  exit(-1);
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;
  if (hyper_parameter == 0)  hyper_parameter = 30;

  Matrix *A = NULL;
  A = ReadMatrix(input_filename);
  Matrix *U = GetIdentityMatrix(A->columns);
  Matrix *V = GetIdentityMatrix(A->columns);
  Matrix *Z = CreateNewMatrix(A->columns, A->columns);
  SVD(A, U, Z, V, hyper_parameter);

  printf("after SVD(U, S, V) \n");
  printf("U = \n");
  WriteMatrix(stdout, U);
  printf("\n");
  printf("S = \n");
  WriteMatrix(stdout, Z);
  printf("\n");
  printf("V = \n");
  WriteMatrix(stdout, V);
  printf("\n");

  int initial_dimensions = 4;
  int final_dimensions = 2;
  Matrix* W = CreateProjectionMatrix(U, initial_dimensions, final_dimensions);
  //WriteMatrix(stdout, W);

  Matrix *Y = Product(A, W);
  WriteMatrix(fout, Y);

  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }
  return 0;
}
