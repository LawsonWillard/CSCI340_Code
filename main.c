
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint64
#include <time.h>	//clock_gettime
#include <math.h>
#include <string.h>

#define KB 1024
#define BILLION 1E9
#define HUNDRED_MILLION 1E8

void cache_block_size()
{
	//time stuff
	uint64_t diff;
	struct timespec start, end;

	int size_of_array = BILLION / 10;
	char* arr = calloc(size_of_array, sizeof(char));


	int num_test_values = 10;
	int test_values[num_test_values];

	int i;
	long j;

	for (i = 0; i < num_test_values; i++)
	{
		test_values[i] = pow(2, i);
	}

	printf("---BLOCK SIZES---\n");
	for (i = 0; i < num_test_values; i++)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		for (j = 0; j < HUNDRED_MILLION; j++)
		{
			++arr[(j * test_values[i]) % size_of_array];
		}
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

		printf("%d : %lfns \n", test_values[i], (double)((long long unsigned int)diff) / HUNDRED_MILLION);
	}
	printf("\n");

	free(arr);
}

void cache_size()
{
	//time stuff
	uint64_t diff;
	struct timespec start, end;

	//found to be 64 in cache_block_size, needs to be double that
	//to avoid precaching
	int stride = 128;

	char* arr = calloc(HUNDRED_MILLION, sizeof(char));

	int num_test_values = 16;
	int test_values[num_test_values];

	int i;
	long j;

	for (int i = 0; i < num_test_values; i++)
	{
		test_values[i] = pow(2, i) * KB;
	}

	printf("---CACHE SIZES---\n");
	for (i = 0; i < num_test_values; i++)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		for (j = 0; j < HUNDRED_MILLION; j++)
		{
			++arr[(j * stride) % test_values[i]];
		}
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

		printf("%dKB : %lf \n", test_values[i] / KB, (double)((long long unsigned int)diff) / HUNDRED_MILLION);
	}
	printf("\n");

	free(arr);
}

int main()
{
	cache_block_size();
	cache_size();

	return 0;
}
