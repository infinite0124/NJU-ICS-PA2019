#include "cpu/instr.h"

int pop()
{
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	imm.addr=cpu.esp;
	printf("esp=%x\n",cpu.esp);
	operand_write(&imm);
	cpu.esp+=data_size;
	return imm.val;
}
