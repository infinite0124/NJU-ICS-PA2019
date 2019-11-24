#include "numu.h"
#include "memory.h"
#include "memory/memory.h"

struct Cacheline
{
	bool valid;//1
	uint32_t mark;//26-7=19
	uint8_t data[64];//64*8
};

void init_cache();
uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache);
void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache);

