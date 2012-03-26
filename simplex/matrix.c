#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

FRACTION * get_frac(MATRIX * m, int row, int col) {
	return &m->f[m->col * row + col];
}

MATRIX * allocate_matrix(int row, int col) {
	MATRIX * result = (MATRIX *) calloc(sizeof(MATRIX), 1);

	result->row = row;
	result->col = col;
	result->f = (FRACTION *) calloc(sizeof(FRACTION), row * col);

	return (MATRIX *) result;
}

void print_matrix(const MATRIX * m) {
	int i;
	int j;

	printf("----- Matrix %p -----\n", m);
	for (i = 0; i < m->row; i++) {
		for (j = 0; j < m->col; j++) {
			print_fraction(get_frac((MATRIX *) m, i, j));
		}
		printf("\n");
	}
}

void load_from_array(MATRIX * m, int * array) {
	int i;
	int j;

	for (i = 0; i < m->row; i++) {
		for (j = 0; j < m->col; j++) {
			assigni(get_frac(m, i, j), array[m->col * i + j]);
		}
	}
}
