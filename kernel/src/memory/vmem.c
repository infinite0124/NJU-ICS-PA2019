#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE) // number of page tables to cover the vmem

PDE *get_updir();

void create_video_mapping()
{

//	BREAK_POINT
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
	PTE ptable[1024] align_to_page;

	PDE *pdir=(PDE *)va_to_pa(get_updir());
	PTE *pte=(PTE *)va_to_pa(ptable);
	pdir[0].val=make_pde(pte);
	pte+=0xa0;
	for(int i=0xa0;i<=0xaf;i++)
	{
		pte->val=make_pte(i<<12);
		pte++;
	}
	
/*	PTE *ptable=(PTE *)pdir[0].val;
	uint32_t ptable_idx;

		//pdir[pdir_idx].val=make_pde(ptable);
		//pdir[pdir_idx+KOFFSET/PT_SIZE.val]=make_pde(ptable);
	//Log("NR_PT:%x\n",NR_PT);

		for(ptable_idx=0;ptable_idx<1024;ptable_idx++)
		{
			ptable[ptable_idx].val=ptable_idx<<12;
			//ptable->val=make_pte(pframe_idx<<12);
			//pframe_idx++;
		}
		*/
	

	//panic("please implement me");
}

void video_mapping_write_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		buf[i] = i;
	}
}

void video_mapping_read_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		assert(buf[i] == i);
	}
}

void video_mapping_clear()
{
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
