#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

static FRACTION * simplex_iter(MATRIX * m);

FRACTION * simplex(MATRIX * m) {
	int i = 0;
	FRACTION * result;

	PRINT_MATRIX(m);
	while ((result = simplex_iter(m)) == NULL) {
		PRINT("Interation Step %d is done\n", ++i);
		PRINT_MATRIX(m);
	}
	PRINT("End of Simplex\n");

	return result;
}

static int find_pivot_col(MATRIX * m) {
	int i;
	int min_col = 0;
	FRACTION min;
	assigni(&min, 0);

	for (i = 1; i < 10; i++) {
//	for (i = 1; i < m->col - 1; i++) {
//		if (comparef(&min, get_frac(m, 0, i)) > 0) {
		if (comparef(&min, get_frac(m, 0, i)) < 0) {
			assignf(&min, get_frac(m, 0, i));
			min_col = i;
		}
	}

	if (comparei(&min, 0) <= 0)
//	if (comparei(&min, 0) >= 0)
		return -1;

	return min_col;
}

static int find_pivot_row(MATRIX * m, int pivot_col) {
	int i;
	int pivot_row = -1;

	FRACTION min;

	for (i = 1; i < m->row; i++) {
		FRACTION ratio;
		FRACTION * f = get_frac(m, i, pivot_col);
		if (comparei(f, 0) == 0)
			continue;

		divf(&ratio, get_frac(m, i, m->col - 1), f);

		if (comparei(&ratio, 0) == 0 && comparei(f, 0) < 0)
			continue;

		if (pivot_row == -1 || comparef(&ratio, &min) < 0) {
			pivot_row = i;
			assignf(&min, &ratio);
		}
	}
	return pivot_row;
}

static void divide_pivot_row(MATRIX * m, int pivot_row, int pivot_col) {
	int i;
	FRACTION pivot;

	assignf(&pivot, get_frac(m, pivot_row, pivot_col));

	for (i = 0; i < m->col; i++) {
		divf(get_frac(m, pivot_row, i), get_frac(m, pivot_row, i), &pivot);
	}
}

static void eliminate_pivot_col(MATRIX * m, int pivot_row, int pivot_col) {
	int i;
	int j;
	FRACTION pivot;

	assignf(&pivot, get_frac(m, pivot_row, pivot_col));

	for (i = 0; i < m->row; i++) {
		FRACTION v;
		if (i == pivot_row)
			continue;
		
		divf(&v, get_frac(m, i, pivot_col), &pivot);
		for (j = 0; j < m->col; j++) {
			FRACTION s;
			mulf(&s, get_frac(m, pivot_row, j), &v);
			subf(get_frac(m, i, j), get_frac(m, i, j), &s);
		}
		
	}
}

static FRACTION * simplex_iter(MATRIX * m) {
	int pivot_col;
	int pivot_row;

	// step 1: find the pivot column
	pivot_col = find_pivot_col(m);
	PRINT("Pivot Column: %d\n", pivot_col);
	if (pivot_col < 0)
		return get_frac(m, 0, m->col - 1);

	// step 2: find the pivot row and the pivot value
	pivot_row = find_pivot_row(m, pivot_col);
	PRINT("Pivot row: %d\n", pivot_row);

	// step 3: divide the pivot row by the pivot value
	divide_pivot_row(m, pivot_row, pivot_col);

	// step 4: eliminate values in the pivot column from other rows
	eliminate_pivot_col(m, pivot_row, pivot_col);

	return NULL;
}
