#include "cpu/instr.h"

int pop()
{
	opr_src.type=OPR_IMM;
	opr_src.data_size=data_size;
	opr_src.addr=cpu.esp;
	printf("esp=%x\n",cpu.esp);
	operand_read(&opr_src);
	cpu.esp+=data_size;
	printf("opr_src.val=%x\n",opr_src.val);
	return opr_src.val;
}
