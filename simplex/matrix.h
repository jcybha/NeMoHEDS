#include <stdio.h>

#include "fraction.h"

typedef struct {
	int row;
	int col;
	FRACTION * f;
} MATRIX;

#ifdef _DEBUG
#define PRINT_MATRIX(X) print_matrix(X)
#else
#define PRINT_MATRIX(X)
#endif

FRACTION * get_frac(MATRIX * m, int row, int col);
MATRIX * allocate_matrix(int row, int col);

void print_matrix(const MATRIX * m);

void load_from_array(MATRIX * m, int * array);
