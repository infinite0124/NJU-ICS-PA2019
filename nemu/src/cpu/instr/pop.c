#include "cpu/instr.h"

int pop()
{
	OPERAND imm;
	imm.type=OPR_REG;
	imm.data_size=data_size;
	imm.addr=cpu.esp;
	printf("esp=%x\n",cpu.esp);
	operand_read(&imm);
	cpu.esp+=data_size;
	printf("imm.val=%x\n",imm.val);
	return imm.val;
}
