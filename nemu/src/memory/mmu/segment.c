#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	/* perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	uint32_t base=cpu.segReg[sreg].base;
	uint32_t addr=base+offset;
	return addr;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	SegDesc s;
	uint32_t addr=cpu.gdtr.base+8*cpu.segReg[sreg].index;
	printf("addr=%x\n",addr);
	
	memcpy(&s,(void *)addr,1);
	printf("s=%x %x\n",s.val[0],s.val[1]);
	//cpu.segReg[sreg].base=(s.base_31_24<<24)+(s.base_23_16<<16)+s.base_15_0;
	//cpu.segReg[sreg].limit=(s.limit_19_16<<16)+s.limit_15_0;
	//printf("base=%x\n",cpu.segReg[sreg].base);
	//printf("limit=%x\n",cpu.segReg[sreg].limit);

	assert(s.granularity==1||s.present==0||cpu.segReg[sreg].base==0||cpu.segReg[sreg].limit==0xffffffff);

}
