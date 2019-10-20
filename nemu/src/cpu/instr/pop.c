#include "cpu/instr.h"

int pop()
{
	OPERAND imm;
	imm.type=OPR_MEM;
	imm.data_size=32;
	imm.addr=cpu.esp;
	oprand_wirte(&imm);
	cpu.esp+=data_size;
	return imm.val;
}
