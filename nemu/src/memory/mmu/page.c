#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t dir=laddr>>22;
	uint32_t page=(laddr&0x003ff000)>>12;
	uint32_t offset=laddr&0x00000fff;
	assert(cpu.cr0.pe&&cpu.cr0.pg);
	uint32_t cpu.cr3.pdtr+4*dir;
	assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
