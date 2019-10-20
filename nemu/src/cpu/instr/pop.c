#include "cpu/instr.h"

int pop()
{
	OPERAND imm;
	imm.type=OPR_MEM;
	imm.data_size=data_size;
	imm.addr=cpu.esp;
	operand_write(&imm);
	cpu.esp+=data_size;
	return imm.val;
}
