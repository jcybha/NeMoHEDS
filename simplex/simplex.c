#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

static int maximize = 0;

static FRACTION * simplex_iter(MATRIX * m);

FRACTION * simplex(MATRIX * m, int maximize_a) {
	int i = 0;
	FRACTION * result;
	maximize = maximize_a;

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
	int min_col = 1;
	FRACTION min;

	assignf(&min, get_frac(m, 0, 1));
	for (i = 2; i < 4; i++) {
//	for (i = 2; i < m->col - 1; i++) {
//		if (comparef(&min, get_frac(m, 0, i)) > 0) {
		//if (maximize) {
		if (1) {
			if (comparef(&min, get_frac(m, 0, i)) < 0) {
				assignf(&min, get_frac(m, 0, i));
				min_col = i;
			}
		}
		else {
			if (comparef(&min, get_frac(m, 0, i)) > 0) {
				assignf(&min, get_frac(m, 0, i));
				min_col = i;
			}
		}
	}

	if (comparei(&min, 0) <= 0)
		return -1;
#if 0
	if (comparei(&min, 0) <= 0 && maximize)
		return -1;

	if (comparei(&min, 0) > 0 && !maximize)
		return -1;
#endif

	return min_col;
}

static int find_pivot_row(MATRIX * m, int pivot_col) {
	int i;
	int pivot_row = -1;

	FRACTION min;

	for (i = 1; i < m->row - 2; i++) {
		FRACTION ratio;
		FRACTION * f = get_frac(m, i, pivot_col);
		if (comparei(f, 0) == 0)
			continue;

		divf(&ratio, f, get_frac(m, i, m->col - 1));

		if (comparei(&ratio, 0) == 0 && comparei(f, 0) < 0)
			continue;

		if (maximize) {
		//if (1) {
			if (pivot_row == -1 || comparef(&ratio, &min) < 0) {
				pivot_row = i;
				assignf(&min, &ratio);
			}
		} else { /* minimize */
			if (pivot_row == -1 || comparef(&ratio, &min) > 0) {
				pivot_row = i;
				assignf(&min, &ratio);
			}
		}
	}
	return pivot_row;
}

static void divide_pivot_row(MATRIX * m, int pivot_row, int pivot_col, FRACTION *pivot) {
	int i;

	for (i = 0; i < m->col; i++) {
		divf(get_frac(m, pivot_row, i), get_frac(m, pivot_row, i), pivot);
	}
}

static void eliminate_pivot_col(MATRIX * m, int pivot_row, int pivot_col, FRACTION *p) {
	int i;
	int j;

	//printf("pivot row = %d, pivot col = %d, pivot? %d/%d\n", pivot_row, pivot_col, get_frac(m, pivot_row, pivot_col)->num, get_frac(m, pivot_row, pivot_col)->dem);
	FRACTION *pivot = get_frac(m, pivot_row, pivot_col);

	for (i = 0; i < m->row - 2; i++) {
		FRACTION v;
		if (i == pivot_row)
			continue;
		
		divf(&v, get_frac(m, i, pivot_col), pivot);
		printf("pivot = %d/%d\n", pivot->num, pivot->dem);
		printf("m = "); print_fraction(get_frac(m, i, pivot_col)); printf("\n");
		printf("v = "); print_fraction(&v); printf("\n");
		for (j = 0; j < m->col; j++) {
			FRACTION s;
#if 1
			if (i < 2 && j == 5) {
				printf("-------------\n");
				print_fraction(&v);
				printf("\n");
				print_fraction(get_frac(m, pivot_row, j));
				printf("\n");
				print_fraction(get_frac(m, i, j));
				printf("-------------\n");
			}
#endif
			mulf(&s, get_frac(m, pivot_row, j), &v);
			subf(get_frac(m, i, j), get_frac(m, i, j), &s);
#if 1
			if (i < 2 && j == 5) {
				printf("-------------\n");
				print_fraction(&v);
				printf("\n");
				print_fraction(get_frac(m, pivot_row, j));
				printf("\n");
				print_fraction(&s);
				printf("\n");
				print_fraction(get_frac(m, i, j));
				printf("-------------\n");
			}
#endif
		}
		
	}
}

#if 0
static int check_finish(MATRIX * m) {
	int i;
}
#endif

static FRACTION * simplex_iter(MATRIX * m) {
	int pivot_col;
	int pivot_row;
	FRACTION pivot;

	// step 1: find the pivot column
	pivot_col = find_pivot_col(m);
	PRINT("Pivot Column: %d\n", pivot_col);
	if (pivot_col < 0)
		return get_frac(m, 0, m->col - 1);

	// step 2: find the pivot row and the pivot value
	pivot_row = find_pivot_row(m, pivot_col);
	PRINT("Pivot row: %d\n", pivot_row);

	assignf(&pivot, get_frac(m, pivot_row, pivot_col));
	// step 3: divide the pivot row by the pivot value
	divide_pivot_row(m, pivot_row, pivot_col, &pivot);
	print_matrix(m);

	// step 4: eliminate values in the pivot column from other rows
	eliminate_pivot_col(m, pivot_row, pivot_col, &pivot);

#if 0
	// check if finished
	if (check_finish(m))
		return get_frac(m, 0, m->col - 1);
#endif

	return NULL;
}
