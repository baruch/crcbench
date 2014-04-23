#ifndef CRC_TESTS_H
#define CRC_TESTS_H

uint32_t crc32_naive(const char *buf, uint32_t buf_len, uint32_t init_val);

uint32_t crc32_bitwise(const void* data, size_t length, uint32_t previousCrc32);
uint32_t crc32_halfbyte(const void* data, size_t length, uint32_t previousCrc32);
uint32_t crc32_4bytes(const void* data, size_t length, uint32_t previousCrc32);
uint32_t crc32_8bytes(const void* data, size_t length, uint32_t previousCrc32);

uint32_t calculateCRC32C(const void *buf, size_t len, uint32_t crc);

uint32_t crc_pcl(const void * buffer, size_t len, uint32_t crc_init);

#endif
