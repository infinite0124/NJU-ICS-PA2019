#include "cpu/instr.h"

static void instr_execute_2op()
{
	opr_dest.val=opr_src.mem_addr.base+opr_src.mem_addr.scale*opr_src.mem_addr.base;
	operand_write(&opr_dest);
}

make_instr_impl_2op(lea,rm,r,v)
