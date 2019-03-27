Holden Lucas and Charles Willard

1. Cache Block Size:

	We tested cache block size by inputing increasing powers of two, and accessing the array by "jumping" by that power. Starting at 1 and going to 2^10 we found that the there was a large jump in time after n = 6 or a cache block size of 64. This is evident as all the times before were ~10ns but at a block size of 128 this went to ~19. From here on the access time kept jumping up. Because of this we believe that our cache line block is 64.

2. Cache Size:

	For testing cache size we created a large array and stepped through it by the block size found in the last step, multiplied to by two to avoid prefetching. We used modulo to ensure the steps stayed inside increasing powers of two, only accessing array indexes within that modulo block. Our results found a large difference at a cache size of between 2 MB and 4 MB. The time to access the cache up to and including 2 MB was ~10ns. After this the time to access the array increase to ~17ns. For this reason we believe our cache size is between 2K and 4K.

3. Cache and Main Memory Access Time:

	Using the last program to test the size of the cache we can also test the cache access time. Before knowing what the cache size was, it would be reasonable to assume that 2KB is in the the range of the cache size. Because of this we assumed that anything around that access time was assumed to be in the cache. Eventually we found that around 4MB the time to access the array was doubled. This is where we assume that the cache ended and the main memory access starts. On average the time to access the cache was ~10ns. Off of this the time to access the main memory was ~17ns.