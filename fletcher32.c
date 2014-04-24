#include <stdint.h>

#include "crc.h"

#define DO fletch1 += *data++; fletch2 += fletch1; l--;

uint32_t fletcher32(const void *buf1, size_t len, uint32_t fletcher)
{
	(void)fletcher;
	const char *data= buf1;
	uint32_t fletch1 = 0xFFFF;
	uint32_t fletch2 = 0xFFFF;

	while (data && len) {
		size_t l = (len <= 360) ? len : 360;
		len -= l;
		while (l) {
			DO;
		}
		fletch1 = (fletch1 & 0xFFFF) + (fletch1 >> 16);
		fletch2 = (fletch2 & 0xFFFF) + (fletch2 >> 16);
	}
	return (fletch2 << 16) | (fletch1 & 0xFFFF);
}

uint32_t fletcher32_4(const void *buf1, size_t len, uint32_t fletcher)
{
	(void)fletcher;
	const char *data = buf1;
	uint32_t fletch1 = 0xFFFF;
	uint32_t fletch2 = 0xFFFF;

	while (data && len) {
		size_t l = (len <= 360) ? len : 360;
		len -= l;
		while (l) {
			DO;
			DO;
			DO;
			DO;
		}
		fletch1 = (fletch1 & 0xFFFF) + (fletch1 >> 16);
		fletch2 = (fletch2 & 0xFFFF) + (fletch2 >> 16);
	}
	return (fletch2 << 16) | (fletch1 & 0xFFFF);
}
