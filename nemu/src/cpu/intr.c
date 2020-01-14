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
	//printf("base=%x,limit=%x\n",cpu.idtr.base,cpu.idtr.limit);
	//printf("base=%x,limit=%x\n",cpu.gdtr.base,cpu.gdtr.limit);

	uint32_t addr=cpu.idtr.base+8*intr_no;
	printf("addr=%x\n",addr);
	GateDesc gatedesc;
	memcpy(&gatedesc,hw_mem+addr,8);
	printf("type:%x\n",gatedesc.type);
	
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
