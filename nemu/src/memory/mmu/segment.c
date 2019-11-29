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
	uint32_t addr=cpu.gdtr.base+8*cpu.segReg[sreg].index;
	SegDesc.val=addr;
	cpu.segReg[sreg].base=SegDesc.base_31_24<<24+SegDesc.base_23_16<<16+SegDesc.base_15_0;
	cpu.segReg[sreg].limit=SegDesc.limit_19_16<<16+SegDesc.limit_15_0;
	assert(SegDesc.granularity==1||SegDesc.present==0||cpu.segReg[sreg].base==0||cpu.segReg[sreg].limit==0xffffffff);

}
