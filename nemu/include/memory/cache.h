#include "nemu.h"
#include "memory.h"
#include "memory/memory.h"

typedef struct
{
	bool valid;//1
	uint32_t mark;//26-7=19
	uint8_t data[64];//64*8
}Cacheline;

void init_cache();
uint32_t cache_read (paddr_t paddr , size_t len , Cacheline *cache);
void cache_write (paddr_t paddr , size_t len , uint32_t data, Cacheline *cache);

