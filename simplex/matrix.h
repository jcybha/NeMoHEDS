#include <stdio.h>

#include "fraction.h"

typedef struct {
	int row;
	int col;
	FRACTION * f;
} MATRIX;

FRACTION * get_frac(MATRIX * m, int row, int col);
MATRIX * allocate_matrix(int row, int col);

void print_matrix(const MATRIX * m);

void load_from_array(MATRIX * m, int * array);
