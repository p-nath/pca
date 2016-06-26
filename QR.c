#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void QR_Decomposition(Matrix* B, Matrix* Q, Matrix* R) {
  double t, r, c, s;
  Matrix* P = NULL; 
  Matrix* Q_temp = NULL;
  Matrix* G = NULL;
  Matrix* G_t = NULL;
  if (B->rows > B->columns)
    G = CreateNewMatrix(B->rows, B->rows);
  else {
    G = CreateNewMatrix(B->columns, B->columns);
  }
  //Givens rotation
  CopyMatrix(R, B);
  for (int co = 0; co < B->columns; co++) {
    for (int count = B->rows-1; count > 0+co; count--) {
      t = R->data[count][co];
      r = sqrt(pow(R->data[count-1][co], 2) + pow(t, 2));
      c = R->data[count-1][co]/r;
      s = t/r;
      //printf("%lf %lf %lf %lf\n", t, r, c, s); if(bidiagonal){}
      //break;
      for (int i = 0; i < G->rows; i++) {
        //if (t == 0 && r == 0)  break;
        for (int j = 0; j < G->columns; j++) {
          if ((i == count-1 && j == count-1) || (i == count && j == count))  G->data[i][j] = c;
          else if (i == count-1 && j == count)  G->data[i][j] = -1*s;
          else if (i == count && j == count-1)  G->data[i][j] = s;
          else if (i == j)  G->data[i][j] = 1;
          else  G->data[i][j] = 0;
        }
      }
      G_t = Transpose(G);
      P = Product(G_t, R);
      CopyMatrix(R, P);
      //WriteMatrix(stdout, G);line
      //WriteMatrix(stdout, R);line
      //WriteMatrix(stdout, Q);line
      Q_temp = Product(Q, G);
      CopyMatrix(Q, Q_temp);
      DestroyMatrix(Q_temp); 
      DestroyMatrix(G_t);
      DestroyMatrix(P);
    }
  }
  DestroyMatrix(G);
}
