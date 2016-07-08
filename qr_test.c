#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "qr.h"

#define FALSE 0
#define TRUE 1

int parse_args(int argc, char** argv, char **input_filename, 
                  char **output_filename, int* hyper_parameter) {
  if (argc >= 3 && arg[1] == "-i"){
    *input_filename = argv[2];
    if (argc >= 5 && arg[3] == "-o"){
      *output_filename = argv[4];
    }
    return TRUE;
  }
  else {
    printf("%s -i <input_filename> -o <output_filename>\n", argv[0]);
    return FALSE;
  }
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  int hyper_parameter = 0;
  if (!parse_args(argc, argv, &input_filename, &output_filename, &hyper_parameter))  exit(-1);
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;

  Matrix *B= NULL;
  B = ReadMatrix(input_filename);
  WriteMatrix(stdout, B);
  printf("\n");

  Matrix *Q = GetIdentityMatrix(B->rows), *R = CreateNewMatrix(B->rows, B->columns);
  QR_Decomposition(B, Q, R);
  printf("Q = \n");
  WriteMatrix(stdout,Q);
  printf("\n R = \n");
  WriteMatrix(stdout, R);
  printf("\n");
  //WriteMatrix(stdout, Product(Q, R));

  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }
  return 0;
}

