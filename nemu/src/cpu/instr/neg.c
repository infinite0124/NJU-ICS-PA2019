#include "cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	if(opr_src.val==0)
		cpu.eflags.CF=0;
	else
		cpu.eflags.CF=1;
}

make_instr_impl_1op(neg,rm,b)
make_instr_impl_1op(neg,rm,v)