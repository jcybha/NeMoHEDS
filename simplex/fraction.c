#include <stdio.h>

#include "fraction.h"

int is_valid(const FRACTION * f) {
	return (f->dem != 0);
}

int is_integer(const FRACTION * f) {
	return (f->dem == 1);
}

int gcd(int a, int b) {
	int c;

	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	if (a < b) {
		c = a;
		a = b;
		b = c;
	}

	while (1) {
		c = a % b;
		if (c == 0)
			break;
		a = b;
		b = c;
	}
		
	return b;
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

void standardize(FRACTION * f) {
	int gcd_;

	if (f->num == 0) {
		f->dem = 1;
		return;
	}

	gcd_ = gcd(f->num, f->dem);
	if (gcd_ > 1)
	f->num /= gcd_;
	f->dem /= gcd_;

	if (f->dem < 0) {
		f->num = -f->num;
		f->dem = -f->dem;
	}
}

void addf(FRACTION * t, const FRACTION * f1, const FRACTION * f2) {
	if (f1->dem == f2->dem) {
		t->num = f1->num + f2->num;
		t->dem = f1->dem;
		return;
	}
	int gcd_ = gcd(f1->dem, f2->dem);

	t->num = f1->num * f1->dem / gcd_ + f2->num * f2->dem / gcd_;
	t->dem = f1->dem * f2->dem / gcd_;

	standardize(t);
}

void subf(FRACTION * t, const FRACTION * f1, const FRACTION * f2) {
	if (f1->dem == f2->dem) {
		t->num = f1->num - f2->num;
		t->dem = f1->dem;
		return;
	}
	int gcd_ = gcd(f1->dem, f2->dem);

	t->num = f1->num * f1->dem / gcd_ - f2->num * f2->dem / gcd_;
	t->dem = f1->dem * f2->dem / gcd_;

	standardize(t);
}

void mulf(FRACTION * t, const FRACTION * f1, const FRACTION * f2) {
	t->num = f1->num * f2->num;
	t->dem = f1->dem * f2->dem;

	standardize(t);
}

void divf(FRACTION * t, const FRACTION * f1, const FRACTION * f2) {
	if (f2 != t) {
		t->num = f1->num * f2->dem;
		t->dem = f1->dem * f2->num;
	}
	else {
		int n = f1->num * f2->dem;
		t->dem = f1->dem * f2->num;
		t->num = n;
	}

	standardize(t);
}

void addi(FRACTION * t, const FRACTION * f, int v) {
	t->num = f->num + v * f->dem;
	t->dem = f->dem;
}

void subi(FRACTION * t, const FRACTION * f, int v) {
	t->num = f->num - v * f->dem;
	t->dem = f->dem;
}

void muli(FRACTION * t, const FRACTION * f, int v) {
	t->num = f->num * v;
	t->dem = f->dem;

	standardize(t);
}

void divi(FRACTION * t, const FRACTION * f, int v) {
	t->num = f->num;
	t->dem = f->dem * v;

	standardize(t);
}

void assigni(FRACTION * f, int v) {
	f->num = v;
	f->dem = 1;
}

void assignf(FRACTION * f1, const FRACTION * f2) {
	f1->num = f2->num;
	f1->dem = f2->dem;
}

int comparei(const FRACTION * f, int v) {
	if (!is_integer(f))
		return f->num - v * f->dem;
	return (f->num - v);
}

int comparef(const FRACTION * f1, const FRACTION * f2) {
	if (f1->dem == f2->dem) {
		return (f1->num - f2->num);
	}
	int gcd_ = gcd(f1->dem, f2->dem);

	return (f1->num * f1->dem / gcd_ - f2->num * f2->dem / gcd_);
}

void print_fraction(const FRACTION * f) {
	if (is_integer(f))
		printf("%d", f->num);
	else
		printf("%d/%d", f->num, f->dem);
}
