#include "cpu/instr.h"

int call_rel(uint32_t eip,uint8_t opcode)
{
	int len=1;
	push_eip();
	uint32_t imm=instr_fetch(eip+1,data_size/8);
	cpu.eip+=imm;
	if(data_size==16)
		cpu.eip=cpu.eip&0x0000ffff;
	len+=data_size;
	return len;
}
