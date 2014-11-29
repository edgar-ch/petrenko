#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct bmp_f_header {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} __attribute__ ((__packed__));

struct bmp_header_v3 {
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} __attribute__ ((__packed__));

int main()
{
	int i, fd_inp, fd_out, rbytes;
	ssize_t rd;
	struct bmp_header_v3 header;
	struct bmp_f_header f_header;
	uint8_t *buf;

	fd_inp = open("25.BMP", O_RDONLY);
	fd_out = open("res.bmp", O_WRONLY|O_TRUNC|O_CREAT, 0666);

	read(fd_inp, &f_header, sizeof(struct bmp_f_header));
	//lseek(fd_inp, 0xA, SEEK_SET);
	//read(fd_inp, &f_header.bfOffBits, 4);
	lseek(fd_inp, 0xE, SEEK_SET);
	read(fd_inp, &header, sizeof(struct bmp_header_v3));

	printf("Type: %x\n", f_header.bfType);
	printf("Size: %x\n", f_header.bfSize);
	printf("Reserved1: %x\n", f_header.bfReserved1);
	printf("Reserved2: %x\n", f_header.bfReserved2);
	printf("Offset: %x\n", f_header.bfOffBits);

	printf("Size: %u\n", header.biSize);
	printf("Width: %u\n", header.biWidth);
	printf("Height: %u\n", header.biHeight);
	printf("Planes: %u\n", header.biPlanes);
	printf("BitCount: %u\n", header.biBitCount);

	rbytes = header.biHeight / 4 + header.biHeight % 4;
	buf = (uint8_t *) malloc(rbytes);

	write(fd_out, &f_header, sizeof(struct bmp_f_header));
	write(fd_out, &header, sizeof(struct bmp_header_v3));
	lseek(fd_inp, f_header.bfOffBits, SEEK_SET);
	lseek(fd_out, f_header.bfOffBits, SEEK_SET);

	while (1) {
		rd = read(fd_inp, buf, rbytes);
		if (rd == 0)
			break;
		for (i = 0; i < rbytes; i += 3) {
			buf[i] &= 0;
			buf[i + 1] &= 0;
			buf[i + 2] &= 0xFF;
		}
		write(fd_out, buf, rbytes);
	}

	close(fd_out);
	close(fd_inp);
	exit(EXIT_SUCCESS);
}
