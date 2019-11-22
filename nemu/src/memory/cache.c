#include "memory/cache.h"
Cacheline cache[1024];

void init_cache()
{
	for(int i=0;i<1024;i++)
		cache[i].valid=0;
}

uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache)
{
	
}

void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache)
{

}
