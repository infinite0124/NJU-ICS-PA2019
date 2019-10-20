#include "cpu/instr.h"

static void instr_execute_1op()
{
	//if(data_size==16)
		//cpu.gpr[4].val-=16;
	//else if(data_size==32)
		//cpu.gpr[4].val-=32;
	operand_read(&opr_src);
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.gpr[4]._32;
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)


