#include <string.h>
#include <stdlib.h>

#include "simplex.h"

#define DEBUG 0

#if 0 /* The testing without input text */
#define TEST_SET 0
#if TEST_SET
#define SOLUTIONSIZE 7 
#define VARIABLESIZE 19
char *x[] = {"", 
            "X11", "X12", "X13", 
            "X21", "X22", "X23", 
            "X31", "X32", "X33", 
            "S1", "S2", "S3", 
            "S4", "S5", "S6", 
            "M1", "M2", "M3"}; /* variable name array */
int r[] = {0, 
    16, 17, 18, 
    13, 14, 15, 
    0, 0, 0, 
    0, 0, 0, 
    0, 0, 0, 
    0, 0, 0};
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
#define SOLUTIONSIZE 4
#define VARIABLESIZE 7
char *x[] = {"", "X1", "X2", "S1", "S2", "A1", "A2"}; /* variable name array */
int r[] = {0, 5, 6, 4, 0, 0, 0};
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
    int i = 0;
#if TEST_SET	
	MATRIX * m = allocate_matrix(10, 20);
#else
	//MATRIX * m = allocate_matrix(4, 7);
	MATRIX * m = allocate_matrix(7, 8);
#endif
	load_from_array(m, v);

	/* 1 : maximize */
	print_fraction(simplex(x, r, m, 0));
	printf("\n");

    printf("\n");
    for (i = 1; i < SOLUTIONSIZE; i++) {
        printf("%s ", x[r[i]]);
        print_fraction(get_frac(m, r[i], VARIABLESIZE));
    printf(", ");
    }
    printf("\n");

	return 0;
}
#else
int main(int argc, char **argv) {
    int i;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    FILE *fp = NULL;
    int currentLine = 0;
    int wordCount = 0;

    int SOLUTIONSIZE = 0;
    char **x = NULL;
    int VARIABLESIZE = 0;
    int *r = NULL;
    int matrixRow = 0;
    int matrixCol = 0;
    int *v = NULL;
    MATRIX *m = NULL;

    if (argc != 2)
        return -1;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return -1;
    }

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        //fwrite(line, linelen, 1, stdout);
        char *sep = "\t\n";
        char *word, *brkt;

        if (currentLine <= 6)
            wordCount = 0;

        for (word = strtok_r(line, sep, &brkt);
                word;
                word = strtok_r(NULL, sep, &brkt))
        {
            //printf("%s ", word);
            switch (currentLine) {
                case 0: { /* VARIABLESIZE */
                    VARIABLESIZE = atoi(word);
                    printf("VARIABLESIZE = %d\n", VARIABLESIZE);
                    x = malloc(sizeof(char*)*VARIABLESIZE);
                    memset(x, 0x00, sizeof(char*)*VARIABLESIZE);
                    for (i = 0; i < VARIABLESIZE; i++)
                        x[i] = malloc(sizeof(char)*VARNAMESIZE);
                }
                    break;
                case 1: { /* Save variable name */
                    strncpy(x[wordCount], word, strlen(word));
                }
                    break;
                case 2: { /* Save initial Variabla */
                    SOLUTIONSIZE = atoi(word);
                    printf("SOLUTIONSIZE = %d\n", SOLUTIONSIZE);
                    /* To access the solutions later,
                     * we have to alloc the size of 'r' as VARIABLESIZE, not SOLUTIONSIZE */
                    r = malloc(sizeof(int)*VARIABLESIZE);
                    memset(r, 0x00, sizeof(int)*VARIABLESIZE);
                }
                    break;
                case 3: {
                    r[wordCount] = atoi(word);
                }
                    break;
                case 4: /* Matrix col */
                    matrixCol = atoi(word);
                    break;
                case 5:{/* Matrix row */
                    matrixRow = atoi(word);
                    v = malloc(sizeof(int)*matrixRow*matrixCol);
                    memset(v, 0x00, sizeof(int)*matrixRow*matrixCol);
                    m = allocate_matrix(matrixRow, matrixCol);
                }
                    break;
                default: {
                    char numBuf[10]; int isMul = 0;
                    int wordLen = strlen(word), i = 0;
                    int isMinus = 0; int isBIGM = 0;
                    if (DEBUG) printf("word %s, count %d\n", word, wordCount);

                    for (i = 0; i < wordLen; ++i) {
                        char c = word[i];
                        if (c == '-')
                            isMinus = 1;
                        if (c == 'M') {
                            if (DEBUG) printf("isBIGM\n");
                            isBIGM = 1;
                        }
                        if (c == '*') {
                            isMul = 1;
                            strncpy(numBuf, word, i);
                            if (DEBUG) printf("Numbuf - %s (WORD : %s)\n", numBuf, word);
                        }
                    }

                    if (isMul && isBIGM) {
                        v[wordCount] = atoi(numBuf) * BIG_M;
                        if (DEBUG) printf("isMul && isBIGM = %d\n", v[wordCount]);
                    }
                    else if (isMinus && isBIGM)
                        v[wordCount] = -BIG_M;
                    else if (isBIGM)
                        v[wordCount] = BIG_M;
                    else
                        v[wordCount] = atoi(word);
                }
                    break;
            }
            wordCount++;
        }
        
        if (currentLine == 1) {
            int i = 0;
            printf("Initial Variable name\n");
            for (; i < VARIABLESIZE; i++) {
                printf("%s ", x[i]);
            }
            printf("\n");
        }
        if (currentLine == 3) {
            int i = 0;
            printf("Initial Variable \n");
            for (; i < SOLUTIONSIZE; i++) {
                printf("%d ", r[i]);
            }
            printf("\n");
        }
        currentLine++;
    }

    load_from_array(m, v);
    print_matrix(m);

    fclose(fp);

    /* Do Simplex, and get solutions */
	print_fraction(simplex(x, r, m, 0));
	printf("\n");

    printf("\n");
    for (i = 1; i < SOLUTIONSIZE; i++) {
        printf("%s ", x[r[i]]);
        print_fraction(get_frac(m, r[i], VARIABLESIZE));
    printf(", ");
    }
    printf("\n");
    return 0;
}
#endif
