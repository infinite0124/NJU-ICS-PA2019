#include "cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	printf("addr=%x,oval=%x\n",opr_src.addr,opr_src.val);
	opr_src.val=~opr_src.val;
	printf("val=%x\n",opr_src.val);
	operand_write(&opr_src);
}

make_instr_impl_1op(not,rm,v)
