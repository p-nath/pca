#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.h"
#include "qr.h"

void help(char** argv) {
  printf("%s -i <input_filename> -o <output_filename>\n", argv[0]);
}

bool parse_args(int argc, char** argv, char **input_filename, 
                  char **output_filename) {
  if (argc < 3)  
    return false;
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i+1 < argc) {
      i++;
      *input_filename = argv[i];
    }
    if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
      i++;
      *output_filename = argv[i];
    }
  }
  return true;
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  if (!parse_args(argc, argv, &input_filename, &output_filename)) {
    help(&argv[0]);
    exit(-1);
  }
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;

  Matrix *B= NULL;
  B = ReadMatrix(input_filename);
  WriteMatrix(stdout, B);
  printf("\n");

  Matrix *Q = GetIdentityMatrix(B->rows), *R = CreateNewMatrix(B->rows, B->columns);
  QR_Decomposition(B, Q, R);
  fprintf(fout, "Q = \n");
  WriteMatrix(fout, Q);
  fprintf(fout, "\nR = \n");
  WriteMatrix(fout, R);
  fprintf(fout, "\n");
  //WriteMatrix(stdout, Product(Q, R));

  if (!(fout == stdout)) {
    printf("Output was written in %s\n", output_filename);
    fclose(fout);
  }
  return 0;
}

