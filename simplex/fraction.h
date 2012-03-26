#include <stdio.h>

typedef struct {
	int num; /* numerator */
	int dem; /* demoninator */
} FRACTION;


int is_valid(const FRACTION * f);
int is_integer(const FRACTION * f);
int gcd(int a, int b);
int lcm(int a, int b);
void standardize(FRACTION * f);
void addf(FRACTION * t, const FRACTION * f1, const FRACTION * f2);
void subf(FRACTION * t, const FRACTION * f1, const FRACTION * f2);
void mulf(FRACTION * t, const FRACTION * f1, const FRACTION * f2);
void divf(FRACTION * t, const FRACTION * f1, const FRACTION * f2);

void addi(FRACTION * t, const FRACTION * f, int v);
void subi(FRACTION * t, const FRACTION * f, int v);
void muli(FRACTION * t, const FRACTION * f, int v);
void addi(FRACTION * t, const FRACTION * f, int v);

void assigni(FRACTION * f, int v);
void assignf(FRACTION * f1, const FRACTION * f2);
int comparei(const FRACTION * f, int v);
int comparef(const FRACTION * f1, const FRACTION * f2);

void print_fraction(const FRACTION * f);
