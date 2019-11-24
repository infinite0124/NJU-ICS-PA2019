#include "memory/cache.h"
#include "memory.h"
#include <stdio.h>
#include "memory/memory.h"
#include "nemu.h"
#include <time.h>
#include <stdlib.h>

Cacheline cache[1024];

void init_cache()
{
	for(int i=0;i<1024;i++)
		cache[i].valid=0;
}

uint32_t cache_read (paddr_t paddr , size_t len , Cacheline *cache)
{
	int gr_num=(paddr&0x00001fc0)>>6;//7
	int sign=(paddr&0xffffe000)>>13;//19
	int addr=paddr&0x0000003f;//6
	uint32_t ret=0;
	//printf("paddr=%x,gr_num=%x,sign=%x,addr=%x\n",paddr,gr_num,sign,addr);
	for(int pos=gr_num*8;pos<gr_num*8+8;pos++)
	{
		if(cache[pos].valid&&(cache[pos].mark==sign))//hit
		{
			memcpy(&ret,cache[pos].data+addr,len);
			uint32_t ans=0;
			memcpy(&ans,hw_mem+paddr,len);
		//	printf("ans=%x,ret=%x\n",ans,ret);
			if(ans!=ret)
			{
				printf("paddr=%x,addr=%x,ans=%x,ret=%x\n",paddr,addr,ans,ret);
				for(int i=0;i<64;i++)
					 printf("%x,",cache[pos].data[i]);
				printf("\n");
				memcpy(cache[pos].data,hw_mem+(paddr&0xffffffc0),64);
				for(int i=0;i<64;i++)
					printf("%x,",cache[pos].data[i]);

				printf("\n");
			}
			return ret;
		}
	}
	//read from memory
	memcpy(&ret,hw_mem+paddr,len);
	//printf("addr=%x,len=%x,ret=%x\n",addr,len,ret);
	//find an empty place
	for(int pos=gr_num*8;pos<gr_num*8+8;pos++)
	{
		if(!cache[pos].valid)
		{
			
			memcpy(cache[pos].data,hw_mem+(paddr&0xffffffc0),64);
			//for(int i=0;i<64;i++)
			//	printf("%x, ",cache[pos].data[i]);
			//printf("\n");
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
	memcpy(cache[pos].data,hw_mem+(paddr&0xffffffc0),64);
	return ret;
}

void cache_write (paddr_t paddr , size_t len , uint32_t data, Cacheline *cache)
{
	memcpy(hw_mem+paddr,&data,len);
	int gr_num=(paddr&0x00001fc0)>>6;//7
        int sign=(paddr&0xffffe000)>>13;//19
	
	for(int pos=gr_num*8;pos<gr_num*8+8;pos++)
	{
		if(cache[pos].valid&&cache[pos].mark==sign)
			memcpy(cache[pos].data,&data,len);
	}

}
