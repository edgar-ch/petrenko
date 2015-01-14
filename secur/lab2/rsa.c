#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct res {
	uint64_t d, x, y;
};

uint64_t sum_mod(uint64_t, uint64_t, uint64_t);
uint64_t prois_mod(uint64_t, uint64_t, uint64_t);
uint64_t step_mod(uint64_t, uint64_t, uint64_t);
struct res evklid(uint64_t, uint64_t);
uint64_t inv_mod(uint64_t, uint64_t);

int main(int argc, char **argv)
{
	uint64_t n, m, d;
	uint64_t p = 4294965737, q = 3087007667, e = 1912934161;
	uint64_t msg = 4012748617, enc, dec;
	
	n = p*q;
	m = (p - 1) * (q - 1);
	d = inv_mod(e, m); 
	printf("d = %lu\n", d);
	enc = step_mod(msg, e, n);
	printf("Enc = %lu\n", enc);
	dec = step_mod(enc, d, n);
	printf("Dec = %lu\n", dec);
	//printf("D = %ld, x = %ld, y = %ld\n", answ.d, answ.x, answ.y);
	
	return 0;
}

// сумма чисел a и b по модулю mod
uint64_t sum_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	if ((a + b >= mod) || (a + b < b))
		return a + b - mod;
	else
		return a + b;
}
// произведение чисел a и b по модулю mod
uint64_t prois_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	int i;
	uint64_t mask = 0x8000000000000000;
	uint64_t res = 0;

	for (i = 0; i < 63; mask = mask >> 1, i++) {
		if (a && (b & mask))
			res = sum_mod(a, res, mod);
		else
			res = sum_mod(0, res, mod);
		res = sum_mod(res, res, mod);
	}
	res = sum_mod(a * (a && (b & mask)), res, mod);

	return res;
}
// возведение числа a в степень b по модулю mod
uint64_t step_mod(uint64_t a, uint64_t b, uint64_t mod)
{
	int i;
	uint64_t mask = 0x8000000000000000;
	uint64_t res = 1;

	for (i = 0; i < 63; mask = mask >> 1, i++) {
		if (a && (b & mask))
			res = prois_mod(a, res, mod);
		else
			res = prois_mod(1, res, mod);
		res = prois_mod(res, res, mod);
	}
	res = prois_mod(a * (a && (b & mask)), res, mod);

	return res;
}

struct res evklid(uint64_t a, uint64_t b)
{
	struct res ret;
	uint64_t x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	uint64_t q, r, x, y;
	
	if (b == 0) {
		ret.d = a;
		ret.x = 1;
		ret.y = 0;
		return ret;
	}
	
	while (b > 0) {
		q = a/b;
		r = a - q*b;
		x = x2 - q*x1;
		y = y2 - q*y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}
	
	ret.d = a;
	ret.x = x2;
	ret.y = y2;
	
	return ret;
}
		
uint64_t inv_mod(uint64_t a, uint64_t m)
{
	struct res ret;
	
	ret = evklid(a, m);
	if (ret.d == 1)
		return ret.x;
		
	return 0;
}
