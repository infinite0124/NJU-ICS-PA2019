#include "cpu/instr.h"

make_instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest=alu_and(opr_src.val,opr_dest.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(and,i,rm,v)
