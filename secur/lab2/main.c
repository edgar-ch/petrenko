#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct res {
	uint64_t d, x, y;
};

struct res evklid(uint64_t, uint64_t);
uint64_t inv_mod(uint64_t, uint64_t);

int main(int argc, char **argv)
{
	uint64_t a, b, inv;
	struct res answ;
	
	puts("A:");
	scanf("%ld", &a);
	puts("B:");
	scanf("%ld", &b);
	
	answ = evklid(a, b);
	
	printf("D = %ld, x = %ld, y = %ld\n", answ.d, answ.x, answ.y);
	
	return 0;
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
