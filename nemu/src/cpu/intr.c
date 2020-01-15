#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
	//pushf();
	//push_segReg(1);
	//push_eip();
	printf("intr_no=%x\n",intr_no);

	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);
	cpu.esp-=2;
	vaddr_write(cpu.esp,SREG_SS,2,cpu.cs.val);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);

	assert(intr_no<=cpu.idtr.limit);

	uint32_t laddr=segment_translate(cpu.idtr.base+8*intr_no,2);
	uint32_t paddr=page_translate(laddr);
	
	GateDesc gatedesc;
	memcpy(&gatedesc,hw_mem+paddr,8);

	printf("type=%x\n",gatedesc.type);

	if(gatedesc.type==0xe)
		cpu.eflags.IF=0;
//	else if(gatedesc.type==0xf)
//		cpu.eflags.IF=1;

	cpu.cs.val=gatedesc.selector;
	cpu.cs.base=0;
	cpu.cs.limit=0xfffff;

	cpu.eip=(gatedesc.offset_31_16<<16)+gatedesc.offset_15_0;
	printf("eip=%x\n",cpu.eip);
	
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
