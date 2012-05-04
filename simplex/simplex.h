#include "matrix.h"

#define VARNAMESIZE 128
#define BIG_M 100000

//FRACTION * simplex(MATRIX * m, int maximize_a);
FRACTION * simplex(char *x[], int r[], MATRIX * m, int maximize_a);
