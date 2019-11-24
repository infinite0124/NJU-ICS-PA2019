#include "memory/cache.h"
#include "memory.h"
#include <stdio.h>
#include "memory/memory.h"
#include "nemu.h"
#include "time.h"

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
	uint32_t ret=0;
	for(int pos=gr_num*8;pos<gr_num*8+8;pos++)
	{
		if(cache[pos].valid&&(cache[pos].mark==sign))//hit
		{
			memcpy(&ret,cache[pos].data+8*addr,len);
			return ret;
		}
	}
	//read from memory
	memcpy(&ret,hw_mem+paddr,len);
	//find an empty place
	for(int pos=gr_num*8;pos<gr_num*8+8;pos++)
	{
		if(!cache[pos].valid)
		{
			memcpy(cache[pos].data,hw_mem+paddr,64);
			cache[pos].valid=1;
			cache[pos].mark=sign;
			return ret;
		}
	}
	//the group is full
	srand((unsigned)time(NULL));
	int pos=gr_num*8+rand()%8;
	cache[pos].valid=1;
	cache[pos].mark=sign;
	memcpy(cache[pos].data,hw_mem+paddr,64);
	return ret;
}

void cache_write (paddr_t paddr , size_t len , uint32_t data, CacheLine *cache)
{

}
