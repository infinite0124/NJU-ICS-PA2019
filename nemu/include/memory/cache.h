struct Cacheline
{
	int valid;
	int mark[];
	int data[];
};

init_cache();
uint32_t cache_read (paddr_t paddr , size_t len , CacheLine *cache);

