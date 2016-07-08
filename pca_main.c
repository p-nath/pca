#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include "svd.h"

#define FALSE 0
#define TRUE 1

void help(char** argv) {
  printf("%s -i <input_filename> -o <output_filename> -m <max_iterations>\n", argv[0]);
}

int parse_args(int argc, char** argv, char **input_filename, 
                  char **output_filename, int* max_iterations) {
  if (argc >= 3) {
    if (!strcmp(argv[1], "-i"))  *input_filename = argv[2];
    else {
      help(argv);
      return FALSE;
    }
    if (argc >= 5) {
      if (!strcmp(argv[3], "-o"))  *output_filename = argv[4];
      else {
        help(argv);
        return FALSE;
      }
      if (argc == 7) {
        if (!strcmp(argv[5], "-m"))  *max_iterations = atoi(argv[6]);    
        else {
          help(argv);
          return FALSE;
        }
      }
    }
  }
  else {
    help(argv);
    return FALSE;
  }
  return TRUE;
}

int main(int argc, char **argv) {
  char *input_filename = NULL, *output_filename = NULL;
  int max_iterations = 0;
  if (!parse_args(argc, argv, &input_filename, &output_filename, &max_iterations))  exit(-1);
  FILE *fout = NULL;
  if (!(fout = fopen(output_filename,"w")))  fout = stdout;
  if (max_iterations <= 0)  max_iterations = 30;

  Matrix *A = NULL;
  A = ReadMatrix(input_filename);
  Matrix *U = GetIdentityMatrix(A->columns);
  Matrix *V = GetIdentityMatrix(A->columns);
  Matrix *Z = CreateNewMatrix(A->columns, A->columns);
  SVD(A, U, Z, V, max_iterations);

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
  //printf("Enter number of dimensions (<4):");
  //scanf("%d",&final_dimensions);
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
