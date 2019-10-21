#include "cpu/instr.h"

static void instr_execute_2op()
{
	operand_read(&opr_src);
	dest.val=src.val;
	operand_write(&dest);
}

make_instr_impl_2op(lea,m,r,v)
