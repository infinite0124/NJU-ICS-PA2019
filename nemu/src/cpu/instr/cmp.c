#include "cpu/instr.h"

static void instr_execute_2op()
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	printf("opr_src=%x,opr_dest=%x\n",opr_src.val,opr_dest.val);
	int t=sign_ext(opr_src.val,data_size);
	alu_sub(t,opr_dest.val,data_size);
	
	//operand_write(&opr_dest);
}
make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,i,rm,bv);
make_instr_impl_2op(cmp,i,rm,v);
make_instr_impl_2op(cmp,r,rm,v);
make_instr_impl_2op(cmp,r,rm,b);
make_instr_impl_2op(cmp,rm,r,b);
make_instr_impl_2op(cmp,rm,r,v);
make_instr_impl_2op(cmp,i,a,b);
make_instr_impl_2op(cmp,i,a,v)

