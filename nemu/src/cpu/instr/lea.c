#include "cpu/instr.h"

static void instr_execute_2op()
{
	printf("base=%x,scale=%x,index=%x\n",opr_src.mem_addr.base,opr_src.mem_addr.scale,opr_src.mem_addr.index);
	//opr_dest.val=cpu.gpr[opr_src.mem_addr.base].val+cpu.gpr[opr_src.mem_addr.index].val*opr_src.mem_addr.scale;
	opr_dest.val=opr_src.addr;
	operand_write(&opr_dest);
}

make_instr_impl_2op(lea,rm,r,v)
