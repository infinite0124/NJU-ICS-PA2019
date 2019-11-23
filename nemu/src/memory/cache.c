#include "memory/cache.h"
Cacheline cache[1024];

void init_cache()
{
	for(int i=0;i<1024;i++)
		cache[i].valid=0;
}

uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache)
{
	int gr_num=(paddr&0x00001fc0)>>6;//
	int sign=(paddr&0xffffe000)>>13;
	int addr=paddr&0x0000003f;
	for(int i=0;i<8;i++)
	{
		if(cache[gr_num*8+i].valid&&(cache[gr_num*8+i].mark==sign))//
		{
			
		}
	}

}

void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache)
{

}
