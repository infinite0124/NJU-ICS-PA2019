#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	pushf();
	push_segReg(1);
	push_eip();
	assert(intr_no<=cpu.idtr.limit);
	printf("base=%x,limit=%x\n",cpu.idtr.base,cpu.idtr.limit);
	uint32_t addr=hw_mem+cpu.idtr.base+8*intr_no;
	print("addr=%x\n",addr);
	GateDesc gatedesc;
	memcpy(&gatedesc,addr,8);
	
	
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
