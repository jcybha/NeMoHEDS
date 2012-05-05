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
int parse_input_and_simplex(char *inputfilename) {
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

    fp = fopen(inputfilename, "r");
    if (fp == NULL) {
        printf("Cannot open %s\n", inputfilename);
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
        print_fraction(get_frac(m, i, VARIABLESIZE));
    printf(", ");
    }
    printf("\n");

    /* Free Memory */
    for (i = 0; i < VARIABLESIZE; ++i)
        free(x[i]);
    free(x);
    free(v);
    free(r);
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp = NULL, *fpout = NULL;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    int i = 0, j = 0;

    int currentFormular = 0;
    int isSkippedFormularP = 0;
    int numFormula = 0;
    int numVariable = 0;
    int numS = 0;
    int numM = 0;
    int Coeff[100][100];
    int S[100];
    int M[100];

    memset(Coeff, 0x00, sizeof(int)*100*100);
    memset(S, 0x00, sizeof(int)*100);
    memset(M, 0x00, sizeof(int)*100);

    if (argc != 2)
        return -1;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return -1;
    }

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        char *sep = "\t\n";
        char *word, *brkt;

        /* If numFormula == 0, current line is the P = 30*(x11 + x12 + x13) + 80*(x21 + ... */
        if (numFormula == 0) {
            for (word = strtok_r(line, sep, &brkt);
                    word;
                    word = strtok_r(NULL, sep, &brkt)) {
                numVariable++;
                Coeff[0][numVariable] = atoi(word);
            }
        } else {
            for (word = strtok_r(line, sep, &brkt);
                    word;
                    word = strtok_r(NULL, sep, &brkt)) {
                if (!(word[0] >= '0' && word[0] <= '9')) {
                    if (word[0] == 'G') { /* GT => -Sn + Mn */
                        S[numFormula] = -1;
                        numS++;
                        M[numFormula] = 1;
                        numM++;
                    } else if (word[0] == 'L') { /* LT => +Sn */
                        S[numFormula] = 1;
                        numS++;
                    } else if (word[0] == 'E') { /* EQ => +Mn */
                        M[numFormula] = 1;
                        numM++;
                    }
                }
            }
        }
        numFormula++;
    }
    numFormula--; /* Decrease one count becase of P = ... */

    fclose(fp);
    fp = fopen(argv[1], "r");
    fpout = fopen("/tmp/inter.txt", "w");

    fprintf(fpout, "%d\n", 1 + numVariable + numS + numM);
    fprintf(fpout, "NU ");
    for (i = 1; i < numVariable + 1; ++i)
        fprintf(fpout, "X%d\t", i);
    for (i = 1; i < numS + 1; ++i)
        fprintf(fpout, "S%d\t", i);
    for (i = 1; i < numM; ++i)
        fprintf(fpout, "M%d\t", i);
    fprintf(fpout, "M%d\n", i);

    fprintf(fpout, "%d\n%d\t", 1 + numFormula, 0);
    {
        int noMoreM = 0;
        int cntM = numVariable + 1;
        int cntS = numVariable + 1;
        for (i = 1; i < numFormula; ++i) {
            if(!noMoreM) {
                fprintf(fpout, "%d\t", numS + cntM);
                cntM++;
                if ((cntM - 1 - numVariable) == numM)
                    noMoreM = 1;
            } else {
                fprintf(fpout, "%d\t", cntS);
                cntS++;
            }
        }
        fprintf(fpout, "%d\n", cntS);
    }

    /* Matrix col */
    fprintf(fpout, "%d\n", 1 + numVariable + numS + numM + 1);

    /* Matrix row, 3 for Cj, Zj, Cj-Zj */
    fprintf(fpout, "%d\n", 1 + numFormula + 3);

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        char *sep = "\t\n";
        char *word, *brkt;
        int didMeetGTLTEQ = 0;
        int totalValue = 0;
        int coefCnt = 1;

        if (!isSkippedFormularP) {
            isSkippedFormularP = 1;
            fprintf(fpout, "1\t");
            for (word = strtok_r(line, sep, &brkt);
                    word;
                    word = strtok_r(NULL, sep, &brkt)) {
                fprintf(fpout, "%s\t", word);
            }
            for (i = 0; i < numS + numM; ++i)
               fprintf(fpout, "0\t"); 
            fprintf(fpout, "0\n"); 

            currentFormular++;
            continue;
        }

        /* Now, read and set S1...Sn , M1...Mn */
        if (M[currentFormular] == 1)
            fprintf(fpout, "M\t");
        else
            fprintf(fpout, "0\t");
        for (word = strtok_r(line, sep, &brkt);
                word;
                word = strtok_r(NULL, sep, &brkt)) {
            if (!(word[0] >= '0' && word[0] <= '9'))
                didMeetGTLTEQ = 1;
            if (!didMeetGTLTEQ) {
                fprintf(fpout, "%s\t", word);
                Coeff[currentFormular][coefCnt] = atoi(word);
                coefCnt++;
            }
            else {
                totalValue = atoi(word);
            }
        }
        for (i = 1; i < numS + 1; ++i) {
            if (currentFormular == i) {
                fprintf(fpout, "%d\t", S[i]);
                Coeff[currentFormular][coefCnt] = S[i];
            }
            else
                fprintf(fpout, "0\t");
            coefCnt++;
        }
        for (i = 1; i < numM + 1; ++i) {
            if (currentFormular == i) {
                fprintf(fpout, "%d\t", M[i]);
                Coeff[currentFormular][coefCnt] = M[i];
            }
            else
                fprintf(fpout, "0\t");
            coefCnt++;
        }
        fprintf(fpout, "%d\n", totalValue);
        Coeff[currentFormular][coefCnt] = totalValue;

        currentFormular++;
    }

    /* Cj */
    for (i = 0; i < 1 + numVariable + numS + numM; ++i) {
        if (i == 0)
            fprintf(fpout, "1\t");
        else if (i >= 1 && i < 1 + numVariable) {
            fprintf(fpout, "%d\t", Coeff[0][i]);
        } else if (i >= 1 + numVariable && i < 1 + numVariable + numS)
            fprintf(fpout, "0\t");
        else if (i >= 1 + numVariable + numS && i < 1 + numVariable + numS + numM)
            fprintf(fpout, "M\t");
    }
    fprintf(fpout, "0\n");

    /* Zj */
    fprintf(fpout, "0\t");
    for (i = 1; i < 1 + numVariable + numS + numM; ++i) {
        int colSum = 0;
        for (j = 1; j < numM + 1; j++)
            colSum = colSum + Coeff[j][i];
        if (colSum == -1)
            fprintf(fpout, "-M\t");
        else if (colSum == 1)
            fprintf(fpout, "M\t");
        else if (colSum != 0)
            fprintf(fpout, "%d*M\t", colSum);
        else
            fprintf(fpout, "0\t");
    }
    fprintf(fpout, "0\n");

    /* Cj - Zj */
    for (i = 0; i < 1 + numVariable + numS + numM; ++i)
        fprintf(fpout, "0\t");
    fprintf(fpout, "0\n");

    fclose(fp);
    fclose(fpout);

    /*DEBUG*/
    /*
    for (j = 0; j < 1 + numFormula + 3; j++) {
        for (i = 0; i < 1 + numVariable + numS + numM; i++)
            printf("%d\t", Coeff[j][i]);
        printf("%d\n", Coeff[j][i]);
    }
    */

    parse_input_and_simplex("/tmp/inter.txt");

    return 0;
}
#endif
