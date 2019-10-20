#include "cpu/instr.h"

int call_rel(uint32_t eip,uint8_t opcode)
{
	push_eip();
	uint32_t imm=instr_fetch(eip+1,data_size);
	cpu.eip+=imm;
	if(data_size==16)
		cpu.eip=cpu.eip&0x0000ffff;
}
