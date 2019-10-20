#include "cpu/instr.h"

int call_rel(uint32_t eip,uint8_t opcode)
{
	int len=1;
	//push_eip();
	//printf("esp=%x\n",cpu.esp);
	uint32_t imm=instr_fetch(eip+1,data_size/8);
	printf("original_eip=%x\n",cpu.eip);
	printf("imm=%x\n",imm);
	len+=data_size/8;
	cpu.eip+=8*len;
	push_eip();
	cpu.eip=cpu.eip+imm;
	if(data_size==16)
		cpu.eip=cpu.eip&0x0000ffff;
	printf("eip=%x\n",cpu.eip);
	return 0;
}
