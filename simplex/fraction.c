#include <stdio.h>

#include "fraction.h"

int is_valid(const FRACTION * f) {
	return (f->dem != 0);
}

int is_integer(const FRACTION * f) {
	return (f->dem == 1) || (f->num == 0);
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
	if (f1->num == 0) {
		t->num = f2->num;
		t->dem = f2->dem;
		return ;
	}
	if (f2->num == 0) {
		t->num = f1->num;
		t->dem = f1->dem;
		return ;
	}
	if (f1->dem == f2->dem) {
		t->num = f1->num + f2->num;
		t->dem = f1->dem;
		standardize(t);
		return;
	}
	int lcm_ = lcm(f1->dem, f2->dem);

	t->num = f1->num * lcm_ /f1->dem + f2->num * lcm_ / f2->dem;
	t->dem = lcm_;

	standardize(t);
}

void subf(FRACTION * t, const FRACTION * f1, const FRACTION * f2) {
	if (f1->num == 0) {
		t->num = -f2->num;
		t->dem = f2->dem;
		return ;
	}
	else if (f2->num == 0) {
		t->num = f1->num;
		t->dem = f1->dem;
		return ;
	}

//printf("f1->num %d f1->dem %d f2->dem %d\n", f1->num, f1->dem, f2->dem);

	if (f1->dem == f2->dem) {
		t->num = f1->num - f2->num;
		t->dem = f1->dem;
		standardize(t);
		return;
	}

	int lcm_ = lcm(f1->dem, f2->dem);

	t->num = f1->num * lcm_ / f1->dem - f2->num * lcm_ / f2->dem;
	t->dem = lcm_;
//printf("f1 %d %d f2 %d %d t %d %d \n", f1->num, f1->dem, f2->num, f2->dem, t->num, t->dem);

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
	int lcm_ = lcm(f1->dem, f2->dem);

	return (f1->num * lcm_ / f1->dem - f2->num * lcm_ / f2->dem);
}

void print_fraction(const FRACTION * f) {
	if (is_integer(f))
		printf("%d", f->num);
	else
		printf("%d/%d", f->num, f->dem);
}

int sprint_fraction(char * str, const FRACTION * f) {
	if (is_integer(f))
		return sprintf(str, "%d", f->num);
	else
		return sprintf(str, "%d/%d", f->num, f->dem);
}
