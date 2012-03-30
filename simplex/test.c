#include "simplex.h"
#define BIG_M 100000
#define TEST_SET 1
#if TEST_SET
int v[] = { 
	1, 	30, 30, 30, 80, 80, 80, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 		0, // P 

	BIG_M,	600,	0,	0,	10,	0,	0,	200,	0,	0,	-1,	0,	0,	0,	0,	0,	1,	0,	0,		300,
	BIG_M,	0,	100,	0,	0,	200,	0,	0,	10,	0,	0,	-1,	0,	0,	0,	0,	0,	1,	0,		100,
	BIG_M,	0,	0,	20,	0,	0,	100,	0,	0,	200,	0,	0,	-1,	0,	0,	0,	0,	0,	1,		200,
	0, 	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,			1,
	0, 	0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,			1,
	0, 	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,			1,

	1,	30, 30, 30, 80, 80, 80, 10, 10, 10, 0, 0, 0, 0, 0, 0, BIG_M, BIG_M, BIG_M,	0, // Cj
	0,	600*BIG_M, 100*BIG_M, 20*BIG_M, 10*BIG_M, 200*BIG_M, 100*BIG_M, 200*BIG_M, 10*BIG_M, 200*BIG_M, -BIG_M, -BIG_M, -BIG_M, 0, 0, 0, BIG_M, BIG_M, BIG_M,	0, // Zj
	0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			0, // Cj - Zj
};
#else
int v[] = { 
	    1,     	1, 2, 0, 0, BIG_M, BIG_M,			0, // p

	    BIG_M, 	1, 3,  0, 0, 1, 0,				3,
   	    BIG_M, 	3, 4, -1, 0, 0, 1,				6,
	    0,     	2, 1, 0, 1, 0, 0,				3,

	    1,     1, 2, 0, 0, BIG_M, BIG_M,				0, // cj
	    0,     4*BIG_M, 7*BIG_M, -BIG_M, 0, BIG_M, BIG_M, 		0, // zj
	    0,     0, 0, 0, 0, 0, 0, 					0, // cj - zj
};
#endif
int main() {
#if TEST_SET	
	MATRIX * m = allocate_matrix(10, 20);
#else
	//MATRIX * m = allocate_matrix(4, 7);
	MATRIX * m = allocate_matrix(7, 8);
#endif
	load_from_array(m, v);

	/* 1 : maximize */
	print_fraction(simplex(m, 0));
	printf("\n");

	return 0;
}
