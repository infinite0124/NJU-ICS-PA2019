#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	pushf();
	push_segReg(1);
	push_eip();
	printf("eip=%x\n",cpu.eip);
	assert(intr_no<=cpu.idtr.limit);
	//printf("base=%x,limit=%x\n",cpu.idtr.base,cpu.idtr.limit);
	//printf("base=%x,limit=%x\n",cpu.gdtr.base,cpu.gdtr.limit);

	uint32_t addr=cpu.idtr.base+8*intr_no;
	//printf("intr_no=%x\n",intr_no);
	//printf("addr=%x\n",addr);
	GateDesc gatedesc;
	memcpy(&gatedesc,hw_mem+addr-0xc0000000,8);
	printf("type:%x\n",gatedesc.type);
	if(gatedesc.type==0xe)
		cpu.eflags.IF=0;

	cpu.cs.val=gatedesc.selector;
	cpu.cs.base=0;
	cpu.cs.limit=0xfffff;

	cpu.eip=(gatedesc.offset_31_16<<16)+gatedesc.offset_15_0;
	//cpu.eip+=9;

	printf("eip=%x\n",cpu.eip);

#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
