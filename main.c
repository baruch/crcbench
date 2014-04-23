#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>

#include "platform.h"
#include "crc.h"

typedef uint32_t (*test_func_t)(const void *data, size_t length, uint32_t init_val);

struct crc_funcs {
	const char *name;
	test_func_t func;
};

static struct crc_funcs crc_funcs[] = {
	{.name = "crc32_bitwise", .func = crc32_bitwise },
	{.name = "crc32_halfbyte", .func = crc32_halfbyte },
	{.name = "crc32_4bytes", .func = crc32_4bytes },
	{.name = "crc32_8bytes", .func = crc32_8bytes },
	{.name = "crc32_sse42", .func = calculateCRC32C},
	{.name = "crc_intel", .func= crc_pcl},
};

static void fill_buf(void *data, size_t data_size)
{
	int fd = open("/dev/urandom", O_RDONLY);
	ssize_t ret = read(fd, data, data_size);
	if (ret < (ssize_t)data_size) {
		printf("Read %d bytes, expected %u\n", ret, data_size);
	}
	close(fd);
}

static void test_buf(test_func_t func, const void *buf, size_t buf_size, uint64_t *result)
{
	volatile uint64_t begin, end;
	
	begin = rdtsc();
	func(buf, buf_size, 0);
	end = rdtsc();
	*result = end - begin;
}

int result_cmp(const void *a, const void *b)
{
	const uint64_t *a1 = a, *b1 = b;
	return (int)(*a1 - *b1);
}

static void test_bufsize(test_func_t func, size_t buf_size, size_t num_iters)
{
	void *buf = malloc(buf_size);
	uint64_t *results = calloc(num_iters, sizeof(uint64_t));

	size_t iter;

	for (iter = 0; iter < num_iters; iter++) {
		fill_buf(buf, buf_size);
		test_buf(func, buf, buf_size, &results[iter]);
	}

	qsort(results, num_iters, sizeof(results[0]), result_cmp);
	printf("Results: %10"PRIu64" %10"PRIu64" %10"PRIu64" %10"PRIu64" %10"PRIu64"\n", results[num_iters/6], results[num_iters*2/6], results[num_iters*3/6], results[num_iters*4/6], results[num_iters*5/6]);

	free(results);
	free(buf);
}

static void test(test_func_t func)
{
	int i;
	size_t buf_size;

	for (i = 1, buf_size = 1024; i <= 10; i++, buf_size *= 2) {
		printf(" Testing buf size %u\n", buf_size);
		size_t num_iters = 25;
		test_bufsize(func, buf_size, num_iters);
	}
}

int main()
{
	int i;
	int ret;
	struct sched_param sparam = {.sched_priority = 50};

	ret = setpriority(PRIO_PROCESS, 0, -20);
	printf("Priority set, ret=%d: %m\n", ret);
	sched_setscheduler(0, SCHED_FIFO, &sparam);
	printf("FIFO set, ret=%d: %m\n", ret);

	for (i = 0; i < sizeof(crc_funcs)/sizeof(crc_funcs[0]); i++) {
		printf("Testing %s\n", crc_funcs[i].name);
		fflush(stdout);
		test(crc_funcs[i].func);
		printf("\n");
	}
}
