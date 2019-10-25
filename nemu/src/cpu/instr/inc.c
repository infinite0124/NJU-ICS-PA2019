#include "cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	//printf("opr_src.addr=%x\n",opr_src.addr);
	//printf("opr_src.type=%x\n",opr_src.type);
	//printf("opr_src.data_size%x\n",opr_src.data_size);
	opr_src.val=alu_add(0x1,opr_src.val,data_size);
	operand_write(&opr_src);
	//printf("opr_src.addr=%x\n",opr_src.addr);
	//printf("opr_src.val=%x\n",opr_src.val);
}

make_instr_impl_1op(inc,r,v);
make_instr_impl_1op(inc,rm,v)
