#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int i, fd_inp, fd_out;
	uint32_t offs;
	uint8_t curr_byte, byte = 0x0;
	ssize_t rd;
	
	fd_inp = open("rezult.bmp", O_RDONLY);
	fd_out = open("res.txt", O_WRONLY|O_TRUNC|O_CREAT);
	
	lseek(fd_inp, 0xA, SEEK_SET);
	read(fd_inp, &offs, 4);
	//printf("Offs %d\n", offs);
	lseek(fd_inp, offs, SEEK_SET);
	while (1) {
		for (i = 0; i < 8; i++) {
			rd = read(fd_inp, &curr_byte, 1);
			if (rd == 0) {
				close(fd_out);
				close(fd_inp);
				exit(EXIT_SUCCESS);
			}
			byte = byte << 1;
			byte = byte | (curr_byte % 2);
		}
		write(fd_out, &byte, 1);
		byte = 0x0;
	}
	
	exit(EXIT_SUCCESS);
}
