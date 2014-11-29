#include <stdio.h>
#include <stdint.h>

uint64_t sum_mod(uint64_t, uint64_t, uint64_t);
uint64_t prois_mod(uint64_t, uint64_t, uint64_t);
uint64_t step_mod(uint64_t, uint64_t, uint64_t);

int main()
{
	int i;
	// числа для проверки (6 вариант)
	uint64_t mod[3] = {18446744073635332877u, 18446744073387937093u, 15446744073264239371u};
	uint64_t a[3] = {11844744073635332903u, 9446744073387937219u, 9546714073264239383u};
	uint64_t b[3] = {11844745093635332891u, 9446749073387937173u, 9746744073264239383u};

	for (i = 0; i < 3; i++) {
		printf("A = %lu\nB = %lu\nMod = %lu\n\n", a[i], b[i], mod[i]);
		printf("a+b mod M: %lu\n", sum_mod(a[i], b[i], mod[i]));
		printf("a*b mod M: %lu\n", prois_mod(a[i], b[i], mod[i]));
		printf("a^b mod M: %lu\n\n", step_mod(a[i], b[i], mod[i]));
	}

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
