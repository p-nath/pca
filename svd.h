#ifndef __SVD_H__
#define __SVD_H__

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void QR_Decomposition(Matrix* B, Matrix* Q, Matrix* R);

void QR_Converge(Matrix* B, Matrix* Q, Matrix* Q_t, Matrix* R, int max_iterations);

void SVD(Matrix* A, Matrix* U, Matrix* Z, Matrix* V, int max_iterations);

Matrix* CreateProjectionMatrix(Matrix* U, int initial_dimensions, int final_dimensions);

#endif