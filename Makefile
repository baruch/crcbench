all: crc_test

CFLAGS=-O3 -g -msse4.2 -Wall -Wextra -Werror -D_GNU_SOURCE
LDFLAGS=-g -lpthread

crc_test: crc_brumme.o main.o crc_sse42.o crc_iscsi_v_pcl.o crc-mark-adler.o adler32.o fletcher32.o
	gcc -o $@ $^ ${LDFLAGS}

crc_iscsi_v_pcl.o: crc_iscsi_v_pcl.asm
	yasm -f x64 -f elf64 -X gnu -g dwarf2 -D LINUX -o crc_iscsi_v_pcl.o crc_iscsi_v_pcl.asm

.PHONY: all clean
clean:
	-rm -f *.o crc_test
