#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	if(laddr<0xc0000000)
		printf("laddr:%x\n",laddr);
	uint32_t dir=laddr>>22;
	uint32_t page=(laddr&0x003ff000)>>12;
	uint32_t offset=laddr&0x00000fff;
	assert(cpu.cr0.pe&&cpu.cr0.pg);//
	uint32_t addr=(cpu.cr3.pdtr<<12)+4*dir;
	PDE pde;
	memcpy(&pde,hw_mem+addr,4);
	assert(pde.present==1);//
	uint32_t p_addr=(pde.page_frame<<12)+4*page;
	PTE pte;
	memcpy(&pte,hw_mem+p_addr,4);
	assert(pte.present==1);//
//	assert(pte.page_frame==0);//
	uint32_t res=(pte.page_frame<<12)+offset;
	if(res>0x00040000)
		printf("addr:%x\n",res);
	uint32_t temp;
	memcpy(&temp,hw_mem+res,4);
	//printf("temp:%x\n",temp);
	return (pte.page_frame<<12)+offset;
	//assert(0);
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
	;
#endif
}
