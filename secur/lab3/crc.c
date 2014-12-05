#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int i, fd_inp, rnd = 16;
	ssize_t rd;
	uint16_t r_x = 0x0000, buf = 0x0000, xor = 0x0000;
	uint16_t g_x = 0x15ab;
	
	fd_inp = open(argv[1], O_RDONLY);
	if (fd_inp == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	rd = read(fd_inp, &buf, 2);
	r_x = htobe16(buf);
	while (1) {
		buf = 0x0000;
		rd = read(fd_inp, &buf, 2);
		buf = htobe16(buf);
		for (i = 0; i < rnd; i++) {
			if (xor == 0x8000) {
				r_x ^= g_x;
			}
			xor = r_x & 0x8000;
			r_x <<= 1;
			if (buf & 0x8000)
				r_x |= 0x0001;
			buf <<= 1;
		}
		if (rd == 1)
			rnd = 8;
		if (rd == 0)
			break;
	}
	
	printf("Result: %x\n", r_x);
	
	exit(EXIT_SUCCESS);
}
