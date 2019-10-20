#include "cpu/instr.h"

static void instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	uint32_t res=alu_and(opr_src.val,opr_dest.val,data_size);
}

make_instr_impl_2op(test,r,rm,v)
