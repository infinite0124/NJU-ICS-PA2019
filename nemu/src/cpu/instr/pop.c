#include "cpu/instr.h"

int pop()
{
	opr_src=mem;
	mem.data_size=data_size;
	mem.addr=cpu.esp;
	printf("esp=%x\n",cpu.esp);
	operand_read(&mem);
	cpu.esp+=data_size;
	printf("mem.val=%x\n",mem.val);
	return mem.val;
}
